#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  recv_buf ;
typedef  int /*<<< orphan*/  port ;
typedef  int /*<<< orphan*/  dest_length ;
struct TYPE_15__ {scalar_t__ Port; scalar_t__ ProxyPort; int* HostName; int* ProxyHostName; int* ProxyUsername; int* ProxyPassword; } ;
typedef  TYPE_1__ WPC_CONNECT ;
typedef  int USHORT ;
typedef  scalar_t__ UINT ;
typedef  int UCHAR ;
struct TYPE_18__ {int /*<<< orphan*/  Size; int /*<<< orphan*/  Buf; } ;
struct TYPE_17__ {int /*<<< orphan*/ * FirstSock; void* Err; scalar_t__ Halt; } ;
struct TYPE_16__ {int* ipv6_addr; int* addr; } ;
typedef  int /*<<< orphan*/  SOCK ;
typedef  TYPE_2__ IP ;
typedef  TYPE_3__ CONNECTION ;
typedef  TYPE_4__ BUF ;

/* Variables and functions */
 int /*<<< orphan*/  CONNECTING_TIMEOUT_PROXY ; 
 int /*<<< orphan*/  Debug (char*,...) ; 
 int /*<<< orphan*/  Disconnect (int /*<<< orphan*/ *) ; 
 void* ERR_DISCONNECTED ; 
 void* ERR_PROXY_AUTH_FAILED ; 
 void* ERR_PROXY_CONNECT_FAILED ; 
 void* ERR_PROXY_ERROR ; 
 void* ERR_USER_CANCEL ; 
 int Endian16 (int) ; 
 int /*<<< orphan*/  Free (int*) ; 
 int /*<<< orphan*/  FreeBuf (TYPE_4__*) ; 
 scalar_t__ INFINITE ; 
 scalar_t__ IsEmptyStr (int*) ; 
 scalar_t__ IsIP6 (TYPE_2__*) ; 
 scalar_t__ IsZeroIp (TYPE_2__*) ; 
 scalar_t__ MIN (int /*<<< orphan*/ ,scalar_t__) ; 
 int* Malloc (int) ; 
 TYPE_4__* NewBuf () ; 
 int* ReAlloc (int*,int) ; 
 int RecvAll (int /*<<< orphan*/ *,int*,int,int) ; 
 int /*<<< orphan*/  ReleaseSock (int /*<<< orphan*/ *) ; 
 int SendAll (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SetTimeout (int /*<<< orphan*/ *,scalar_t__) ; 
 int StrLen (int*) ; 
 int /*<<< orphan*/  StrToIP (TYPE_2__*,int*) ; 
 int /*<<< orphan*/ * TcpConnectEx3 (int*,scalar_t__,scalar_t__,int*,void*,int,int /*<<< orphan*/ *,int,TYPE_2__*) ; 
 int /*<<< orphan*/  WriteBuf (TYPE_4__*,int*,int) ; 

SOCK *Socks5Connect(CONNECTION *c, WPC_CONNECT *w, bool additional_connect, bool *cancel_flag, void *hWnd, UINT timeout, IP *ret_ip)
{
	UCHAR tmp, recv_buf[2], *recv_buf_final;
	USHORT port;
	bool ret;
	SOCK *s;
	BUF *b;
	IP ip;
	// Validate arguments
	if (c == NULL || w == NULL || w->Port == 0 || w->ProxyPort == 0 || IsEmptyStr(w->HostName) || IsEmptyStr(w->ProxyHostName))
	{
		if (c != NULL)
		{
			c->Err = ERR_PROXY_CONNECT_FAILED;
		}
		return NULL;
	}

	if (c->Halt)
	{
		// Stop
		c->Err = ERR_USER_CANCEL;
		return NULL;
	}

	// Open TCP connection to the proxy server
	s = TcpConnectEx3(w->ProxyHostName, w->ProxyPort, timeout, cancel_flag, hWnd, true, NULL, false, ret_ip);
	if (s == NULL)
	{
		// Failure
		c->Err = ERR_PROXY_CONNECT_FAILED;
		return NULL;
	}

	// Set the timeout setting
	SetTimeout(s, MIN(CONNECTING_TIMEOUT_PROXY, (timeout == 0 ? INFINITE : timeout)));

	if (additional_connect == false)
	{
		c->FirstSock = s;
	}

	// +----+----------+----------+
	// |VER | NMETHODS | METHODS  |
	// +----+----------+----------+
	// | 1  |    1     | 1 to 255 |
	// +----+----------+----------+
	//
	// X'00'			NO AUTHENTICATION REQUIRED
	// X'01'			GSSAPI
	// X'02'			USERNAME/PASSWORD
	// X'03' to X'7F'	IANA ASSIGNED
	// X'80' to X'FE'	RESERVED FOR PRIVATE METHODS
	// X'FF'			NO ACCEPTABLE METHOD

	b = NewBuf();
	tmp = 5;
	WriteBuf(b, &tmp, sizeof(tmp));	// SOCKS version
	tmp = 2;
	WriteBuf(b, &tmp, sizeof(tmp));	// Number of supported methods
	tmp = 0;
	WriteBuf(b, &tmp, sizeof(tmp));	// No authentication
	tmp = 2;
	WriteBuf(b, &tmp, sizeof(tmp));	// Username/password

	ret = SendAll(s, b->Buf, b->Size, false);
	FreeBuf(b);

	if (ret == false)
	{
		Debug("Socks5Connect(): [Phase 1] Failed to send initial data to the server.\n");
		c->Err = ERR_DISCONNECTED;
		goto failure;
	}

	// +----+--------+
	// |VER | METHOD |
	// +----+--------+
	// | 1  |   1    |
	// +----+--------+

	if (RecvAll(s, recv_buf, sizeof(recv_buf), false) == false)
	{
		Debug("Socks5Connect(): [Phase 1] Failed to receive initial data response from the server.\n");
		c->Err = ERR_DISCONNECTED;
		goto failure;
	}

	if (recv_buf[0] != 5)
	{
		Debug("Socks5Connect(): [Phase 1] Unmatching version: %u.\n", recv_buf[0]);
		c->Err = ERR_PROXY_ERROR;
		goto failure;
	}

	// Username/password authentication (RFC1929)
	if (recv_buf[1] == 2)
	{
		// +----+------+----------+------+----------+
		// |VER | ULEN |  UNAME   | PLEN |  PASSWD  |
		// +----+------+----------+------+----------+
		// | 1  |  1   | 1 to 255 |  1   | 1 to 255 |
		// +----+------+----------+------+----------+

		b = NewBuf();
		tmp = 1;
		WriteBuf(b, &tmp, sizeof(tmp));		// Authentication protocol version
		tmp = StrLen(w->ProxyUsername);
		WriteBuf(b, &tmp, sizeof(tmp));		// Username length
		WriteBuf(b, w->ProxyUsername, tmp);	// Username
		tmp = StrLen(w->ProxyPassword);
		WriteBuf(b, &tmp, sizeof(tmp));		// Password length
		WriteBuf(b, w->ProxyPassword, tmp);	// Password

		ret = SendAll(s, b->Buf, b->Size, false);
		FreeBuf(b);

		if (ret == false)
		{
			Debug("Socks5Connect(): [Phase 1] Failed to send authentication data to the server.\n");
			c->Err = ERR_DISCONNECTED;
			goto failure;
		}

		// +----+--------+
		// |VER | STATUS |
		// +----+--------+
		// | 1  |   1    |
		// +----+--------+

		if (RecvAll(s, recv_buf, sizeof(recv_buf), false) == false)
		{
			Debug("Socks5Connect(): [Phase 1] Failed to receive authentication data response from the server.\n");
			c->Err = ERR_DISCONNECTED;
			goto failure;
		}

		if (recv_buf[1] != 0)
		{
			Debug("Socks5Connect(): [Phase 1] Authentication failure error code sent by the server: %u.\n", recv_buf[1]);
			c->Err = ERR_PROXY_AUTH_FAILED;
			goto failure;
		}
	}

	// +----+-----+-------+------+----------+----------+
	// |VER | CMD |  RSV  | ATYP | DST.ADDR | DST.PORT |
	// +----+-----+-------+------+----------+----------+
	// | 1  |  1  | X'00' |  1   | Variable |    2     |
	// +----+-----+-------+------+----------+----------+
	//
	// VER				protocol version: X'05'
	// CMD
	// CONNECT			X'01'
	// BIND				X'02'
	// UDP ASSOCIATE	X'03'
	// RSV				RESERVED
	// ATYP				address type of following address
	// IP V4 address	X'01'
	// DOMAINNAME		X'03'
	// IP V6 address	X'04'
	// DST.ADDR			desired destination address
	// DST.PORT			desired destination port in network octet order

	// Prepare data to send
	b = NewBuf();
	tmp = 5;
	WriteBuf(b, &tmp, sizeof(tmp));	// SOCKS version
	tmp = 1;
	WriteBuf(b, &tmp, sizeof(tmp));	// Command
	tmp = 0;
	WriteBuf(b, &tmp, sizeof(tmp));	// Reserved byte

	// Convert the hostname to an IP structure (if it's an IP address)
	StrToIP(&ip, w->HostName);

	// If the IP structure doesn't contain an IP address, it means that the string is an hostname
	if (IsZeroIp(&ip))
	{
		UCHAR dest_length = StrLen(w->HostName);
		tmp = 3;
		WriteBuf(b, &tmp, sizeof(tmp));							// Destination type (hostname)
		WriteBuf(b, &dest_length, sizeof(dest_length));			// Destination hostname length
		WriteBuf(b, w->HostName, dest_length);					// Destination hostname
	}
	else
	{
		if (IsIP6(&ip))
		{
			tmp = 4;
			WriteBuf(b, &tmp, sizeof(tmp));						// Destination type (IPv6)
			WriteBuf(b, ip.ipv6_addr, sizeof(ip.ipv6_addr));	// Destination IPv6 address
		}
		else
		{
			tmp = 1;
			WriteBuf(b, &tmp, sizeof(tmp));						// Destination type (IPv4)
			WriteBuf(b, ip.addr, sizeof(ip.addr));				// Destination IPv4 address
		}
	}

	// Convert the port in network octet order
	port = Endian16((USHORT)w->Port);
	WriteBuf(b, &port, sizeof(port));							// Destination port

	// Send data
	ret = SendAll(s, b->Buf, b->Size, false);
	FreeBuf(b);

	if (ret == false)
	{
		Debug("Socks5Connect(): [Phase 2] Failed to send data to the server.\n");
		c->Err = ERR_DISCONNECTED;
		goto failure;
	}

	// +----+-----+-------+------+----------+----------+
	// |VER | REP |  RSV  | ATYP | BND.ADDR | BND.PORT |
	// +----+-----+-------+------+----------+----------+
	// | 1  |  1  | X’00’ |  1   | Variable |   2      |
	// +----+-----+-------+------+----------+----------+
	//
	// VER protocol version: X’05’
	// REP Reply field:
	// X’00’	succeeded
	// X’01’	general SOCKS server failure
	// X’02’	connection not allowed by ruleset
	// X’03’	Network unreachable
	// X’04’	Host unreachable
	// X’05’	Connection refused
	// X’06’	TTL expired
	// X’07’	Command not supported
	// X’08’	Address type not supported
	// X’09’	to X’FF’ unassigned

	// The packet sent by the server should always have the same size as the one we sent to it.
	// However, there are some implementations which send fixed values (aside from the first 2 bytes).
	// In order to support such implementations, we read the first 4 bytes in order to know the address type before trying to read the rest of the packet.
	recv_buf_final = Malloc(4);

	if (RecvAll(s, recv_buf_final, 4, false) == false)
	{
		Free(recv_buf_final);
		Debug("Socks5Connect(): [Phase 2] Failed to receive response from the server.\n");
		c->Err = ERR_DISCONNECTED;
		goto failure;
	}

	// We only need the first two bytes (version and response code), but we have to read the entire packet from the socket
	recv_buf[0] = recv_buf_final[0];
	recv_buf[1] = recv_buf_final[1];

	// We receive the rest of the packet by knowing the size according to the address type
	switch (recv_buf_final[3])
	{
	case 1:
		// IPv4
		recv_buf_final = ReAlloc(recv_buf_final, 6);			// 4 bytes (IPv4) + 2 bytes (port)
		ret = RecvAll(s, recv_buf_final, 6, false);
		break;
	case 4:
		// IPv6
		recv_buf_final = ReAlloc(recv_buf_final, 18);			// 4 bytes (IPv4) + 2 bytes (port)
		ret = RecvAll(s, recv_buf_final, 18, false);
		break;
	case 3:
		// Hostname
		ret = RecvAll(s, &tmp, 1, false);
		if (ret == true)
		{
			recv_buf_final = ReAlloc(recv_buf_final, tmp + 2);	// Hostname length + 2 bytes (port)
			ret = RecvAll(s, recv_buf_final, tmp + 2, false);
		}
	}

	Free(recv_buf_final);

	if (ret == false)
	{
		Debug("Socks5Connect(): [Phase 2] Malformed response received from the server.\n");
		c->Err = ERR_DISCONNECTED;
		goto failure;
	}

	if (recv_buf[0] != 5)
	{
		Debug("Socks5Connect(): [Phase 2] Unmatching version: %u.\n", recv_buf_final[0]);
		c->Err = ERR_PROXY_ERROR;
		goto failure;
	}

	if (recv_buf[1] == 0)
	{
		// Success
		SetTimeout(s, INFINITE);
		return s;
	}
	else
	{
		Debug("Socks5Connect(): [Phase 2] Connection failed with error: %u\n", recv_buf[1]);
		c->Err = ERR_PROXY_ERROR;
	}

failure:
	if (additional_connect == false)
	{
		c->FirstSock = NULL;
	}

	Disconnect(s);
	ReleaseSock(s);
	return NULL;
}