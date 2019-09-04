#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT64 ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_4__ {int Connected; int WriteBlocked; scalar_t__ AsyncMode; int /*<<< orphan*/  SendNum; int /*<<< orphan*/  SendSize; int /*<<< orphan*/  ssl_lock; int /*<<< orphan*/ * ssl; } ;
typedef  int /*<<< orphan*/  SSL ;
typedef  TYPE_1__ SOCK ;

/* Variables and functions */
 int /*<<< orphan*/  Debug (char*,char*,int,...) ; 
 int /*<<< orphan*/  Disconnect (TYPE_1__*) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SOCK_LATER ; 
 int SSL_ERROR_NONE ; 
 int SSL_ERROR_SSL ; 
 int SSL_ERROR_WANT_READ ; 
 int SSL_ERROR_WANT_WRITE ; 
 int /*<<< orphan*/  SSL_MODE_ENABLE_PARTIAL_WRITE ; 
 int SSL_get_error (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SSL_set_mode (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int SSL_write (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 

UINT SecureSend(SOCK *sock, void *data, UINT size)
{
	int ret, e = SSL_ERROR_NONE;
	SSL *ssl;
	ssl = sock->ssl;

	if (sock->AsyncMode)
	{
		// Asynchronous mode
		SSL_set_mode(ssl, SSL_MODE_ENABLE_PARTIAL_WRITE);
	}

	// Transmission
	Lock(sock->ssl_lock);
	{
		if (sock->Connected == false)
		{
			Unlock(sock->ssl_lock);
			Debug("%s %u SecureSend() Disconnect\n", __FILE__, __LINE__);
			return 0;
		}

		ret = SSL_write(ssl, data, size);
		if (ret < 0)
		{
			e = SSL_get_error(ssl, ret);
		}
	}
	Unlock(sock->ssl_lock);

#ifdef	ENABLE_SSL_LOGGING
	if (ret > 0)
	{
		SockWriteSslLog(sock, data, ret, NULL, 0);
	}
#endif	// ENABLE_SSL_LOGGING

	if (ret > 0)
	{
		// Successful transmission
		sock->SendSize += (UINT64)ret;
		sock->SendNum++;
		sock->WriteBlocked = false;
		return (UINT)ret;
	}
	if (ret == 0)
	{
		// Disconnect
		Debug("%s %u SecureSend() Disconnect\n", __FILE__, __LINE__);
		Disconnect(sock);
		return 0;
	}

	if (sock->AsyncMode)
	{
		// Confirmation of the error value
		if (e == SSL_ERROR_WANT_READ || e == SSL_ERROR_WANT_WRITE || e == SSL_ERROR_SSL)
		{
			sock->WriteBlocked = true;
			return SOCK_LATER;
		}
		Debug("%s %u e=%u\n", __FILE__, __LINE__, e);
	}
	//Debug("%s %u SecureSend() Disconnect\n", __FILE__, __LINE__);
	Disconnect(sock);
	return 0;
}