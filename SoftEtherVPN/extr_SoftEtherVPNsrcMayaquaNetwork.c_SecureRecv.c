#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  c ;
typedef  scalar_t__ UINT64 ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_11__ {int Connected; scalar_t__* Ssl_Init_Async_SendAlert; TYPE_2__* ssl; scalar_t__ AsyncMode; int /*<<< orphan*/  RecvNum; int /*<<< orphan*/  RecvSize; int /*<<< orphan*/  ssl_lock; } ;
struct TYPE_10__ {TYPE_1__* s3; } ;
struct TYPE_9__ {scalar_t__* send_alert; } ;
typedef  TYPE_2__ SSL ;
typedef  TYPE_3__ SOCK ;

/* Variables and functions */
 int /*<<< orphan*/  Debug (char*,char*,int) ; 
 int /*<<< orphan*/  Disconnect (TYPE_3__*) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SOCK_LATER ; 
 scalar_t__ SSL3_AL_FATAL ; 
 int SSL_ERROR_NONE ; 
 int SSL_ERROR_SSL ; 
 int SSL_ERROR_WANT_READ ; 
 int SSL_ERROR_WANT_WRITE ; 
 int SSL_get_error (TYPE_2__*,int) ; 
 int SSL_peek (TYPE_2__*,char*,int) ; 
 int SSL_read (TYPE_2__*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 

UINT SecureRecv(SOCK *sock, void *data, UINT size)
{
	int ret, e = SSL_ERROR_NONE;
	SSL *ssl;

#ifdef UNIX_SOLARIS
	SOCKET_TIMEOUT_PARAM *ttparam;
#endif //UNIX_SOLARIS

	ssl = sock->ssl;

	if (sock->AsyncMode)
	{
		// Confirm whether the data is readable even 1 byte in the case of asynchronous mode.
		// To read data results blocking, if there is no readable data.
		// We must avoid blocking.
		char c;
		Lock(sock->ssl_lock);
		{
			if (sock->Connected == false)
			{
				Unlock(sock->ssl_lock);
				Debug("%s %u SecureRecv() Disconnect\n", __FILE__, __LINE__);
				return 0;
			}
			ret = SSL_peek(ssl, &c, sizeof(c));
		}
		Unlock(sock->ssl_lock);
		if (ret == 0)
		{
			// The communication have been disconnected
			Disconnect(sock);
			Debug("%s %u SecureRecv() Disconnect\n", __FILE__, __LINE__);
			return 0;
		}
		if (ret < 0)
		{
			// An error has occurred
			e = SSL_get_error(ssl, ret);
			if (e == SSL_ERROR_WANT_READ || e == SSL_ERROR_WANT_WRITE || e == SSL_ERROR_SSL)
			{
				if (e == SSL_ERROR_SSL
#if OPENSSL_VERSION_NUMBER < 0x10100000L
					&&
					sock->ssl->s3->send_alert[0] == SSL3_AL_FATAL &&
					sock->ssl->s3->send_alert[0] != sock->Ssl_Init_Async_SendAlert[0] &&
					sock->ssl->s3->send_alert[1] != sock->Ssl_Init_Async_SendAlert[1]
#endif
					)
				{
					Debug("%s %u SSL Fatal Error on ASYNC socket !!!\n", __FILE__, __LINE__);
					Disconnect(sock);
					return 0;
				}
				// Packet has not arrived yet, that is not to be read
				return SOCK_LATER;
			}
		}
	}

	// Receive
	Lock(sock->ssl_lock);
	{
		if (sock->Connected == false)
		{
			Unlock(sock->ssl_lock);
			Debug("%s %u SecureRecv() Disconnect\n", __FILE__, __LINE__);
			return 0;
		}

#ifdef	OS_UNIX
		if (sock->AsyncMode == false)
		{
			sock->CallingThread = pthread_self();
		}
#endif	// OS_UNIX

// Run the time-out thread for SOLARIS
#ifdef UNIX_SOLARIS
		ttparam = NewSocketTimeout(sock);
#endif // UNIX_SOLARIS

		ret = SSL_read(ssl, data, size);

// Stop the timeout thread
#ifdef UNIX_SOLARIS
		FreeSocketTimeout(ttparam);
#endif // UNIX_SOLARIS


#ifdef	OS_UNIX
		if (sock->AsyncMode == false)
		{
			sock->CallingThread = 0;
		}
#endif	// OS_UNIX

		if (ret < 0)
		{
			e = SSL_get_error(ssl, ret);
		}

	}
	Unlock(sock->ssl_lock);

#ifdef	ENABLE_SSL_LOGGING
	if (ret > 0)
	{
		SockWriteSslLog(sock, NULL, 0, data, ret);
	}
#endif	// ENABLE_SSL_LOGGING

	if (ret > 0)
	{
		// Successful reception
		sock->RecvSize += (UINT64)ret;
		sock->RecvNum++;

		return (UINT)ret;
	}
	if (ret == 0)
	{
		// Disconnect the communication
		Disconnect(sock);
		//Debug("%s %u SecureRecv() Disconnect\n", __FILE__, __LINE__);
		return 0;
	}
	if (sock->AsyncMode)
	{
		if (e == SSL_ERROR_WANT_READ || e == SSL_ERROR_WANT_WRITE || e == SSL_ERROR_SSL)
		{
			if (e == SSL_ERROR_SSL
#if OPENSSL_VERSION_NUMBER < 0x10100000L
				&&
				sock->ssl->s3->send_alert[0] == SSL3_AL_FATAL &&
				sock->ssl->s3->send_alert[0] != sock->Ssl_Init_Async_SendAlert[0] &&
				sock->ssl->s3->send_alert[1] != sock->Ssl_Init_Async_SendAlert[1]
#endif
				)
			{
				Debug("%s %u SSL Fatal Error on ASYNC socket !!!\n", __FILE__, __LINE__);
				Disconnect(sock);
				return 0;
			}

			// Packet has not yet arrived
			return SOCK_LATER;
		}
	}
	Disconnect(sock);
	Debug("%s %u SecureRecv() Disconnect\n", __FILE__, __LINE__);
	return 0;
}