#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  openssl_check_buf ;
typedef  int /*<<< orphan*/  ctoken_hash ;
typedef  int /*<<< orphan*/  X ;
typedef  int UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_21__ {int /*<<< orphan*/  SslAcceptSettings; int /*<<< orphan*/  lock; int /*<<< orphan*/  ServerK; int /*<<< orphan*/  ServerX; int /*<<< orphan*/ * CipherList; TYPE_2__* Server; int /*<<< orphan*/  AcceptingSockets; } ;
struct TYPE_20__ {int flag1; TYPE_8__* Cedar; int /*<<< orphan*/  Err; int /*<<< orphan*/ * CToken_Hash; int /*<<< orphan*/  Name; int /*<<< orphan*/  Type; TYPE_1__* FirstSock; } ;
struct TYPE_19__ {int DisableOpenVPNServer; } ;
struct TYPE_18__ {int IsReverseAcceptedSocket; scalar_t__ Type; int /*<<< orphan*/  CipherName; int /*<<< orphan*/  RemoteIP; int /*<<< orphan*/  SslAcceptSettings; int /*<<< orphan*/  RemotePort; int /*<<< orphan*/  RemoteHostname; int /*<<< orphan*/  ref; } ;
typedef  int /*<<< orphan*/  SSL_ACCEPT_SETTINGS ;
typedef  TYPE_1__ SOCK ;
typedef  TYPE_2__ SERVER ;
typedef  int /*<<< orphan*/  K ;
typedef  TYPE_3__ CONNECTION ;

/* Variables and functions */
 int /*<<< orphan*/  AddNoSsl (TYPE_8__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AddRef (int /*<<< orphan*/ ) ; 
 int CONNECTING_TIMEOUT ; 
 int /*<<< orphan*/  CONNECTION_TYPE_OPENVPN ; 
 int /*<<< orphan*/ * CloneK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * CloneX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  Debug (char*,...) ; 
 int /*<<< orphan*/  Dec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DelConnection (TYPE_8__*,TYPE_3__*) ; 
 int /*<<< orphan*/  Disconnect (TYPE_1__*) ; 
 int /*<<< orphan*/  Free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeX (int /*<<< orphan*/ *) ; 
 int GetMachineRand () ; 
 int /*<<< orphan*/  IPToStr (char*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ IS_SPECIAL_PORT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 scalar_t__ OvsCheckTcpRecvBufIfOpenVPNProtocol (int /*<<< orphan*/ *,int) ; 
 int OvsGetNoOpenVpnTcp () ; 
 int OvsPerformTcpServer (TYPE_8__*,TYPE_1__*) ; 
 int Peek (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ReleaseSock (TYPE_1__*) ; 
 int SHA1_SIZE ; 
 int /*<<< orphan*/  SLog (TYPE_8__*,char*,char*,int /*<<< orphan*/ ,...) ; 
 scalar_t__ SOCK_TCP ; 
 int ServerAccept (TYPE_3__*) ; 
 int /*<<< orphan*/  SetTimeout (TYPE_1__*,int) ; 
 int /*<<< orphan*/  SetWantToUseCipher (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int StartSSL (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * ZeroMalloc (int) ; 

void ConnectionAccept(CONNECTION *c)
{
	SOCK *s;
	X *x;
	K *k;
	char tmp[128];
	UCHAR openssl_check_buf[2];
	char *error_details = NULL;
	SERVER *server;
	UCHAR *peek_buf = NULL;
	UINT peek_buf_size = 1500;
	char sni[256] = {0};
	bool native1 = false;
	bool native2 = false;
	bool native3 = false;
	bool no_native = false;
	UINT peek_size = 0;
	UINT initial_timeout = CONNECTING_TIMEOUT;
	bool no_peek_log = false;
	UCHAR ctoken_hash[SHA1_SIZE];
	bool no_write_ctoken_log = false;

	// Validate arguments
	if (c == NULL)
	{
		return;
	}

	Zero(ctoken_hash, sizeof(ctoken_hash));

	peek_buf = ZeroMalloc(peek_buf_size);

	Debug("ConnectionAccept()\n");

	server = c->Cedar->Server;

	// get a socket
	s = c->FirstSock;
	AddRef(s->ref);

	Dec(c->Cedar->AcceptingSockets);

	IPToStr(tmp, sizeof(tmp), &s->RemoteIP);

	SLog(c->Cedar, "LS_CONNECTION_START_1", tmp, s->RemoteHostname, (IS_SPECIAL_PORT(s->RemotePort) ? 0 : s->RemotePort), c->Name);

	// Timeout setting
	initial_timeout += GetMachineRand() % (CONNECTING_TIMEOUT / 2);
	SetTimeout(s, initial_timeout);


	// Peek whether OpenSSL packet
	if (s->IsReverseAcceptedSocket == false)
	{
		if (s->Type == SOCK_TCP && (c->Cedar != NULL && c->Cedar->Server != NULL && c->Cedar->Server->DisableOpenVPNServer == false))
		{
			if (Peek(s, openssl_check_buf, sizeof(openssl_check_buf)) == sizeof(openssl_check_buf))
			{
				if (OvsCheckTcpRecvBufIfOpenVPNProtocol(openssl_check_buf, sizeof(openssl_check_buf)))
				{
					// Detect OpenSSL packet
					Debug("Detect OpenSSL on TCP!\n");

					no_native = true;

					if (OvsGetNoOpenVpnTcp() == false)
					{
						// Do OpenSSL processing
						c->Type = CONNECTION_TYPE_OPENVPN;
						if (OvsPerformTcpServer(c->Cedar, s) == false)
						{
							error_details = "OpenVPN_TCP_Aborted";
						}
					}

					goto ERROR;
				}
			}
		}


	}

	// Specify the encryption algorithm
	Lock(c->Cedar->lock);
	{
		if (c->Cedar->CipherList != NULL)
		{
			SetWantToUseCipher(s, c->Cedar->CipherList);
		}

		x = CloneX(c->Cedar->ServerX);
		k = CloneK(c->Cedar->ServerK);
	}
	Unlock(c->Cedar->lock);

	// Start the SSL communication
	Debug("StartSSL()\n");
	Copy(&s->SslAcceptSettings, &c->Cedar->SslAcceptSettings, sizeof(SSL_ACCEPT_SETTINGS));
	if (StartSSL(s, x, k) == false)
	{
		// Failed
		AddNoSsl(c->Cedar, &s->RemoteIP);
		Debug("Failed to StartSSL.\n");
		FreeX(x);
		FreeK(k);

		error_details = "StartSSL";

		goto ERROR;
	}


	FreeX(x);
	FreeK(k);

	SLog(c->Cedar, "LS_SSL_START", c->Name, s->CipherName);

	Copy(c->CToken_Hash, ctoken_hash, SHA1_SIZE);

	// Accept the connection
	if (ServerAccept(c) == false)
	{
		// Failed
		Debug("ServerAccept Failed. Err = %u\n", c->Err);
		goto ERROR;
	}

	if (c->flag1 == false)
	{
		Debug("%s %u c->flag1 == false\n", __FILE__, __LINE__);
		Disconnect(s);
	}
	DelConnection(c->Cedar, c);
	ReleaseSock(s);

	Free(peek_buf);
	return;

ERROR:
	Debug("ConnectionAccept() Error.\n");


	Disconnect(s);
	DelConnection(c->Cedar, c);
	ReleaseSock(s);
	Free(peek_buf);
}