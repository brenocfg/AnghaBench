#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  server_host_name_tmp ;
typedef  int /*<<< orphan*/  iptmp ;
typedef  int /*<<< orphan*/  basic_str ;
typedef  int /*<<< orphan*/  auth_tmp_str ;
typedef  int /*<<< orphan*/  auth_b64_str ;
struct TYPE_18__ {scalar_t__ ProxyPort; int /*<<< orphan*/  ProxyPassword; int /*<<< orphan*/  ProxyUsername; int /*<<< orphan*/  CustomHttpHeader; int /*<<< orphan*/  Port; int /*<<< orphan*/  ProxyHostName; int /*<<< orphan*/  HostName; } ;
typedef  TYPE_2__ WPC_CONNECT ;
typedef  size_t UINT ;
struct TYPE_21__ {void* Err; int /*<<< orphan*/ * FirstSock; scalar_t__ Halt; TYPE_1__* Cedar; } ;
struct TYPE_20__ {char* Method; int /*<<< orphan*/  Target; } ;
struct TYPE_19__ {size_t NumTokens; int /*<<< orphan*/ * Token; } ;
struct TYPE_17__ {char* HttpUserAgent; } ;
typedef  TYPE_3__ TOKEN_LIST ;
typedef  int /*<<< orphan*/  SOCK ;
typedef  int /*<<< orphan*/  IP ;
typedef  TYPE_4__ HTTP_HEADER ;
typedef  TYPE_5__ CONNECTION ;

/* Variables and functions */
 int /*<<< orphan*/  AddHttpValue (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AddHttpValueStr (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CONNECTING_TIMEOUT_PROXY ; 
 scalar_t__ Cmp (char*,char*,int) ; 
 char* DEFAULT_USER_AGENT ; 
 int /*<<< orphan*/  Disconnect (int /*<<< orphan*/ *) ; 
 void* ERR_PROXY_AUTH_FAILED ; 
 void* ERR_PROXY_CONNECT_FAILED ; 
 void* ERR_PROXY_ERROR ; 
 void* ERR_USER_CANCEL ; 
 int /*<<< orphan*/  Encode64 (char*,char*) ; 
 int /*<<< orphan*/  Format (char*,int,char*,char*,...) ; 
 int /*<<< orphan*/  FreeHttpHeader (TYPE_4__*) ; 
 int /*<<< orphan*/  FreeToken (TYPE_3__*) ; 
 int /*<<< orphan*/ * GetHttpValue (TYPE_4__*,char*) ; 
 size_t INFINITE ; 
 int /*<<< orphan*/  IPToStr (char*,int,int /*<<< orphan*/ *) ; 
 int IsEmptyStr (int /*<<< orphan*/ ) ; 
 scalar_t__ IsStrIPv6Address (char*) ; 
 int MAX_PATH ; 
 int MAX_SIZE ; 
 size_t MIN (int /*<<< orphan*/ ,size_t) ; 
 TYPE_4__* NewHttpHeader (char*,char*,char*) ; 
 int /*<<< orphan*/  NewHttpValue (char*,char*) ; 
 TYPE_3__* ParseToken (int /*<<< orphan*/ ,char*) ; 
 TYPE_4__* RecvHttpHeader (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseSock (int /*<<< orphan*/ *) ; 
 int SendHttpHeader (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  SetTimeout (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  StrCpy (char*,int,int /*<<< orphan*/ ) ; 
 int StrLen (char*) ; 
 int /*<<< orphan*/  StrToIP (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * TcpConnectEx3 (int /*<<< orphan*/ ,scalar_t__,size_t,int*,void*,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 size_t ToInt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UniFormat (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  Zero (char*,int) ; 
 int /*<<< orphan*/  _UU (char*) ; 

SOCK *ProxyConnectEx3(CONNECTION *c, WPC_CONNECT *wpc_connect,
					  bool additional_connect, bool *cancel_flag, void *hWnd,
					  UINT timeout)
{
	SOCK *s = NULL;
	bool use_auth = false;
	char tmp[MAX_SIZE];
	char auth_tmp_str[MAX_SIZE], auth_b64_str[MAX_SIZE * 2];
	char basic_str[MAX_SIZE * 2];
	UINT http_error_code;
	HTTP_HEADER *h;
	char server_host_name_tmp[256];
	UINT i, len;
	// Validate arguments
	if (c == NULL || IsEmptyStr(wpc_connect->ProxyHostName) || wpc_connect->ProxyPort == 0 || IsEmptyStr(wpc_connect->HostName) || wpc_connect->Port == 0)
	{
		if (c != NULL)
		{
			c->Err = ERR_PROXY_CONNECT_FAILED;
		}
		return NULL;
	}

	if ((IsEmptyStr(wpc_connect->ProxyUsername) || IsEmptyStr(wpc_connect->ProxyPassword)) == false)
	{
		use_auth = true;
	}

	if (c->Halt)
	{
		// Stop
		c->Err = ERR_USER_CANCEL;
		return NULL;
	}

	Zero(server_host_name_tmp, sizeof(server_host_name_tmp));
	StrCpy(server_host_name_tmp, sizeof(server_host_name_tmp), wpc_connect->HostName);

	len = StrLen(server_host_name_tmp);

	for (i = 0;i < len;i++)
	{
		if (server_host_name_tmp[i] == '/')
		{
			server_host_name_tmp[i] = 0;
		}
	}

	// Connection
	s = TcpConnectEx3(wpc_connect->ProxyHostName, wpc_connect->ProxyPort, timeout, cancel_flag, hWnd, true, NULL, false, NULL);
	if (s == NULL)
	{
		// Failure
		c->Err = ERR_PROXY_CONNECT_FAILED;
		return NULL;
	}

	// Timeout setting
	SetTimeout(s, MIN(CONNECTING_TIMEOUT_PROXY, (timeout == 0 ? INFINITE : timeout)));

	if (additional_connect == false)
	{
		c->FirstSock = s;
	}

	// HTTP header generation
	if (IsStrIPv6Address(server_host_name_tmp))
	{
		IP ip;
		char iptmp[MAX_PATH];

		StrToIP(&ip, server_host_name_tmp);
		IPToStr(iptmp, sizeof(iptmp), &ip);

		Format(tmp, sizeof(tmp), "[%s]:%u", iptmp, wpc_connect->Port);
	}
	else
	{
		Format(tmp, sizeof(tmp), "%s:%u", server_host_name_tmp, wpc_connect->Port);
	}

	h = NewHttpHeader("CONNECT", tmp, "HTTP/1.0");

	if (IsEmptyStr(wpc_connect->CustomHttpHeader) == false)
	{
		TOKEN_LIST *tokens = ParseToken(wpc_connect->CustomHttpHeader, "\r\n");
		if (tokens != NULL)
		{
			for (i = 0; i < tokens->NumTokens; i++)
			{
				AddHttpValueStr(h, tokens->Token[i]);
			}

			FreeToken(tokens);
		}
	}

	if (GetHttpValue(h, "User-Agent") == NULL)
	{
		AddHttpValue(h, NewHttpValue("User-Agent", (c->Cedar == NULL ? DEFAULT_USER_AGENT : c->Cedar->HttpUserAgent)));
	}

	if (GetHttpValue(h, "Host") == NULL)
	{
		AddHttpValue(h, NewHttpValue("Host", server_host_name_tmp));
	}

	if (GetHttpValue(h, "Content-Length") == NULL)
	{
		AddHttpValue(h, NewHttpValue("Content-Length", "0"));
	}

	if (GetHttpValue(h, "Proxy-Connection") == NULL)
	{
		AddHttpValue(h, NewHttpValue("Proxy-Connection", "Keep-Alive"));
	}

	if (GetHttpValue(h, "Pragma") == NULL)
	{
		AddHttpValue(h, NewHttpValue("Pragma", "no-cache"));
	}

	if (use_auth && GetHttpValue(h, "Proxy-Authorization") == NULL)
	{
		wchar_t tmp[MAX_SIZE];
		UniFormat(tmp, sizeof(tmp), _UU("STATUS_3"), server_host_name_tmp);
		// Generate the authentication string
		Format(auth_tmp_str, sizeof(auth_tmp_str), "%s:%s",
			   wpc_connect->ProxyUsername, wpc_connect->ProxyPassword);

		// Base64 encode
		Zero(auth_b64_str, sizeof(auth_b64_str));
		Encode64(auth_b64_str, auth_tmp_str);
		Format(basic_str, sizeof(basic_str), "Basic %s", auth_b64_str);

		AddHttpValue(h, NewHttpValue("Proxy-Authorization", basic_str));
	}

	// Transmission
	if (SendHttpHeader(s, h) == false)
	{
		// Failure
		if (additional_connect == false)
		{
			c->FirstSock = NULL;
		}
		FreeHttpHeader(h);
		Disconnect(s);
		ReleaseSock(s);
		c->Err = ERR_PROXY_ERROR;
		return NULL;
	}

	FreeHttpHeader(h);

	if (c->Halt)
	{
		// Stop
		if (additional_connect == false)
		{
			c->FirstSock = NULL;
		}
		Disconnect(s);
		ReleaseSock(s);
		c->Err = ERR_USER_CANCEL;
		return NULL;
	}

	// Receive the results
	h = RecvHttpHeader(s);
	if (h == NULL)
	{
		// Failure
		if (additional_connect == false)
		{
			c->FirstSock = NULL;
		}
		FreeHttpHeader(h);
		Disconnect(s);
		ReleaseSock(s);
		c->Err = ERR_PROXY_ERROR;
		return NULL;
	}

	http_error_code = 0;
	if (StrLen(h->Method) == 8)
	{
		if (Cmp(h->Method, "HTTP/1.", 7) == 0)
		{
			http_error_code = ToInt(h->Target);
		}
	}
	FreeHttpHeader(h);

	// Check the code
	switch (http_error_code)
	{
	case 401:
	case 403:
	case 407:
		// Authentication failure
		if (additional_connect == false)
		{
			c->FirstSock = NULL;
		}
		Disconnect(s);
		ReleaseSock(s);
		c->Err = ERR_PROXY_AUTH_FAILED;
		return NULL;

	default:
		if ((http_error_code / 100) == 2)
		{
			// Success
			SetTimeout(s, INFINITE);
			return s;
		}
		else
		{
			// Receive an unknown result
			if (additional_connect == false)
			{
				c->FirstSock = NULL;
			}
			Disconnect(s);
			ReleaseSock(s);
			c->Err = ERR_PROXY_ERROR;
			return NULL;
		}
	}
}