#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  target_port ;
typedef  int /*<<< orphan*/  recv_buf ;
typedef  int /*<<< orphan*/  dest_length ;
typedef  int USHORT ;
typedef  int UINT ;
typedef  int UCHAR ;
struct TYPE_19__ {int /*<<< orphan*/  Size; int /*<<< orphan*/  Buf; } ;
struct TYPE_18__ {int* ipv6_addr; int* addr; } ;
struct TYPE_17__ {scalar_t__ Port; scalar_t__ TargetPort; int* Hostname; int* TargetHostname; scalar_t__ Timeout; int* Username; int* Password; } ;
struct TYPE_16__ {int /*<<< orphan*/ * Sock; int /*<<< orphan*/  ResolvedIp; } ;
typedef  int /*<<< orphan*/  SOCK ;
typedef  TYPE_1__ PROXY_PARAM_OUT ;
typedef  TYPE_2__ PROXY_PARAM_IN ;
typedef  TYPE_3__ IP ;
typedef  TYPE_4__ BUF ;

/* Variables and functions */
 int /*<<< orphan*/  ClearBuf (TYPE_4__*) ; 
 int /*<<< orphan*/  Debug (char*,...) ; 
 int /*<<< orphan*/  Disconnect (int /*<<< orphan*/ *) ; 
 int Endian16 (scalar_t__) ; 
 int /*<<< orphan*/  Free (int*) ; 
 int /*<<< orphan*/  FreeBuf (TYPE_4__*) ; 
 scalar_t__ INFINITE ; 
 int /*<<< orphan*/ * Internal_ProxyTcpConnect (TYPE_2__*,int volatile*,int /*<<< orphan*/ *) ; 
 scalar_t__ IsEmptyStr (int*) ; 
 scalar_t__ IsIP6 (TYPE_3__*) ; 
 scalar_t__ IsZeroIp (TYPE_3__*) ; 
 scalar_t__ MIN (int /*<<< orphan*/ ,scalar_t__) ; 
 int* Malloc (int) ; 
 TYPE_4__* NewBuf () ; 
 int /*<<< orphan*/  PROXY_CONNECTION_TIMEOUT ; 
 int PROXY_ERROR_AUTHENTICATION ; 
 int PROXY_ERROR_CANCELED ; 
 int PROXY_ERROR_CONNECTION ; 
 int PROXY_ERROR_DISCONNECTED ; 
 int PROXY_ERROR_GENERIC ; 
 int PROXY_ERROR_PARAMETER ; 
 int PROXY_ERROR_SUCCESS ; 
 int PROXY_ERROR_TARGET ; 
 int PROXY_ERROR_VERSION ; 
 int* ReAlloc (int*,int) ; 
 int RecvAll (int /*<<< orphan*/ *,int*,int,int) ; 
 int /*<<< orphan*/  ReleaseSock (int /*<<< orphan*/ *) ; 
 int SendAll (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SetTimeout (int /*<<< orphan*/ *,scalar_t__) ; 
 int StrLen (int*) ; 
 int /*<<< orphan*/  StrToIP (TYPE_3__*,int*) ; 
 int /*<<< orphan*/  WriteBuf (TYPE_4__*,int*,int) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 

UINT ProxySocks5Connect(PROXY_PARAM_OUT *out, PROXY_PARAM_IN *in, volatile bool *cancel_flag)
{
	bool dummy_cancel_flag = false;
	UCHAR tmp, recv_buf[2], *recv_buf_final;
	USHORT target_port;
	IP target_ip;
	UINT ret;
	SOCK *s;
	BUF *b;
	// Validate arguments
	if (out == NULL || in == NULL || in->Port == 0 || in->TargetPort == 0 || IsEmptyStr(in->Hostname) || IsEmptyStr(in->TargetHostname))
	{
		return PROXY_ERROR_PARAMETER;
	}

	if (cancel_flag == NULL)
	{
		cancel_flag = &dummy_cancel_flag;
	}
	else if (*cancel_flag)
	{
		return PROXY_ERROR_CANCELED;
	}

	Zero(out, sizeof(PROXY_PARAM_OUT));

	// Open TCP connection to the proxy server
	s = Internal_ProxyTcpConnect(in, cancel_flag, &out->ResolvedIp);
	if (s == NULL)
	{
		return PROXY_ERROR_CONNECTION;
	}

	SetTimeout(s, MIN(PROXY_CONNECTION_TIMEOUT, (in->Timeout == 0 ? INFINITE : in->Timeout)));

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

	if (ret == false)
	{
		FreeBuf(b);
		Debug("ProxySocks5Connect(): [Phase 1] Failed to send initial data to the server.\n");
		ret = PROXY_ERROR_DISCONNECTED;
		goto FAILURE;
	}

	// +----+--------+
	// |VER | METHOD |
	// +----+--------+
	// | 1  |   1    |
	// +----+--------+

	if (RecvAll(s, recv_buf, sizeof(recv_buf), false) == false)
	{
		FreeBuf(b);
		Debug("ProxySocks5Connect(): [Phase 1] Failed to receive initial data response from the server.\n");
		ret = PROXY_ERROR_DISCONNECTED;
		goto FAILURE;
	}

	if (recv_buf[0] != 5)
	{
		FreeBuf(b);
		Debug("ProxySocks5Connect(): [Phase 1] Unmatching version: %u.\n", recv_buf[0]);
		ret = PROXY_ERROR_VERSION;
		goto FAILURE;
	}

	ClearBuf(b);

	// Username/password authentication (RFC1929)
	if (recv_buf[1] == 2)
	{
		// +----+------+----------+------+----------+
		// |VER | ULEN |  UNAME   | PLEN |  PASSWD  |
		// +----+------+----------+------+----------+
		// | 1  |  1   | 1 to 255 |  1   | 1 to 255 |
		// +----+------+----------+------+----------+

		tmp = 1;
		WriteBuf(b, &tmp, sizeof(tmp));	// Authentication protocol version
		tmp = StrLen(in->Username);
		WriteBuf(b, &tmp, sizeof(tmp));	// Username length
		WriteBuf(b, in->Username, tmp);	// Username
		tmp = StrLen(in->Password);
		WriteBuf(b, &tmp, sizeof(tmp));	// Password length
		WriteBuf(b, in->Password, tmp);	// Password

		ret = SendAll(s, b->Buf, b->Size, false);

		ClearBuf(b);

		if (ret == false)
		{
			Debug("ProxySocks5Connect(): [Phase 1] Failed to send authentication data to the server.\n");
			ret = PROXY_ERROR_DISCONNECTED;
			goto FAILURE;
		}

		// +----+--------+
		// |VER | STATUS |
		// +----+--------+
		// | 1  |   1    |
		// +----+--------+

		if (RecvAll(s, recv_buf, sizeof(recv_buf), false) == false)
		{
			Debug("ProxySocks5Connect(): [Phase 1] Failed to receive authentication data response from the server.\n");
			ret = PROXY_ERROR_DISCONNECTED;
			goto FAILURE;
		}

		if (recv_buf[1] != 0)
		{
			Debug("ProxySocks5Connect(): [Phase 1] Authentication failure, error code sent by the server: %u.\n", recv_buf[1]);
			ret = PROXY_ERROR_AUTHENTICATION;
			goto FAILURE;
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
	tmp = 5;
	WriteBuf(b, &tmp, sizeof(tmp));	// SOCKS version
	tmp = 1;
	WriteBuf(b, &tmp, sizeof(tmp));	// Command
	tmp = 0;
	WriteBuf(b, &tmp, sizeof(tmp));	// Reserved byte

	// Convert the hostname to an IP structure (if it's an IP address)
	StrToIP(&target_ip, in->TargetHostname);

	// If the IP structure doesn't contain an IP address, the string should be an hostname
	if (IsZeroIp(&target_ip))
	{
		UCHAR dest_length = StrLen(in->TargetHostname);
		tmp = 3;
		WriteBuf(b, &tmp, sizeof(tmp));										// Destination type (hostname)
		WriteBuf(b, &dest_length, sizeof(dest_length));						// Destination hostname length
		WriteBuf(b, in->TargetHostname, dest_length);						// Destination hostname
	}
	else
	{
		if (IsIP6(&target_ip))
		{
			tmp = 4;
			WriteBuf(b, &tmp, sizeof(tmp));									// Destination type (IPv6)
			WriteBuf(b, target_ip.ipv6_addr, sizeof(target_ip.ipv6_addr));	// Destination IPv6 address
		}
		else
		{
			tmp = 1;
			WriteBuf(b, &tmp, sizeof(tmp));									// Destination type (IPv4)
			WriteBuf(b, target_ip.addr, sizeof(target_ip.addr));			// Destination IPv4 address
		}
	}

	// Convert the port in network octet order
	target_port = Endian16(in->TargetPort);
	WriteBuf(b, &target_port, sizeof(target_port));							// Destination port

	// Send data
	ret = SendAll(s, b->Buf, b->Size, false);
	FreeBuf(b);

	if (ret == false)
	{
		Debug("ProxySocks5Connect(): [Phase 2] Failed to send data to the server.\n");
		ret = PROXY_ERROR_DISCONNECTED;
		goto FAILURE;
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
		Debug("ProxySocks5Connect(): [Phase 2] Failed to receive response from the server.\n");
		ret = PROXY_ERROR_DISCONNECTED;
		goto FAILURE;
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
		recv_buf_final = ReAlloc(recv_buf_final, 18);			// 16 bytes (IPv6) + 2 bytes (port)
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
		Debug("ProxySocks5Connect(): [Phase 2] Malformed response received from the server.\n");
		ret = PROXY_ERROR_DISCONNECTED;
		goto FAILURE;
	}

	if (recv_buf[0] != 5)
	{
		Debug("ProxySocks5Connect(): [Phase 2] Unmatching version: %u.\n", recv_buf_final[0]);
		ret = PROXY_ERROR_VERSION;
		goto FAILURE;
	}

	switch (recv_buf[1])
	{
	case 0:
		// Success
		SetTimeout(s, INFINITE);
		out->Sock = s;
		return PROXY_ERROR_SUCCESS;
	case 3:
	case 4:
	case 5:
		Debug("ProxySocks5Connect(): [Phase 2] Connection to target failed with error: %u\n", recv_buf[1]);
		ret = PROXY_ERROR_TARGET;
		goto FAILURE;
	default:
		Debug("ProxySocks5Connect(): [Phase 2] Connection failed with error: %u\n", recv_buf[1]);
		ret = PROXY_ERROR_GENERIC;
		goto FAILURE;
	}

FAILURE:
	Disconnect(s);
	ReleaseSock(s);
	return ret;
}