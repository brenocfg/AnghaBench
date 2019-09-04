#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  result_ip_str ;
typedef  int /*<<< orphan*/  ip_str ;
typedef  int /*<<< orphan*/  hostname ;
typedef  scalar_t__ UINT64 ;
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_19__ {int /*<<< orphan*/  Size; int /*<<< orphan*/  Buf; } ;
struct TYPE_18__ {int IgnoreRecvErr; int IPv6; } ;
typedef  int /*<<< orphan*/  SOCK_EVENT ;
typedef  TYPE_1__ SOCK ;
typedef  int /*<<< orphan*/  PACK ;
typedef  int /*<<< orphan*/  IP ;
typedef  int /*<<< orphan*/  INTERRUPT_MANAGER ;
typedef  TYPE_2__ BUF ;

/* Variables and functions */
 int /*<<< orphan*/  AddInterrupt (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ * BufToPack (TYPE_2__*) ; 
 scalar_t__ CmpIpAddr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Disconnect (TYPE_1__*) ; 
 int /*<<< orphan*/  Free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeBuf (TYPE_2__*) ; 
 int /*<<< orphan*/  FreeInterruptManager (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreePack (int /*<<< orphan*/ *) ; 
 int GetIP4Ex (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ GetNextIntervalForInterrupt (int /*<<< orphan*/ *) ; 
 scalar_t__ INFINITE ; 
 int /*<<< orphan*/  IPToStr (char*,int,int /*<<< orphan*/ *) ; 
 int IsEmptyStr (char*) ; 
 scalar_t__ IsIP4 (int /*<<< orphan*/ *) ; 
 scalar_t__ IsIP6 (int /*<<< orphan*/ *) ; 
 int IsZeroIp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  JoinSockToSockEvent (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ListenTcpForPopupFirewallDialog () ; 
 scalar_t__ MAX (scalar_t__,int) ; 
 scalar_t__ MAX_NUM_IGNORE_ERRORS ; 
 int MAX_SIZE ; 
 scalar_t__ MIN (scalar_t__,int) ; 
 int /*<<< orphan*/ * Malloc (scalar_t__) ; 
 TYPE_2__* NewBuf () ; 
 int /*<<< orphan*/ * NewInterruptManager () ; 
 int /*<<< orphan*/ * NewPack () ; 
 TYPE_1__* NewRUDPClientDirect (char*,int /*<<< orphan*/ *,scalar_t__,scalar_t__*,scalar_t__,int*,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * NewSockEvent () ; 
 TYPE_1__* NewUDP4ForSpecificIp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddInt (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddInt64 (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  PackAddStr (int /*<<< orphan*/ *,char*,char*) ; 
 scalar_t__ PackCmpStr (int /*<<< orphan*/ *,char*,char*) ; 
 int PackGetBool (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ PackGetInt (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ PackGetInt64 (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PackGetStr (int /*<<< orphan*/ *,char*,char*,int) ; 
 TYPE_2__* PackToBuf (int /*<<< orphan*/ *) ; 
 scalar_t__ Power (int,scalar_t__) ; 
 int /*<<< orphan*/  RUDPGetRegisterHostNameByIP (char*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ RUDP_ERROR_NAT_T_NOT_FOUND ; 
 scalar_t__ RUDP_ERROR_NAT_T_NO_RESPONSE ; 
 scalar_t__ RUDP_ERROR_NAT_T_TWO_OR_MORE ; 
 scalar_t__ RUDP_ERROR_OK ; 
 scalar_t__ RUDP_ERROR_TIMEOUT ; 
 scalar_t__ RUDP_ERROR_UNKNOWN ; 
 scalar_t__ RUDP_ERROR_USER_CANCELED ; 
 scalar_t__ RUDP_TIMEOUT ; 
 scalar_t__ Rand64 () ; 
 scalar_t__ RecvFrom (TYPE_1__*,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  ReleaseSock (TYPE_1__*) ; 
 int /*<<< orphan*/  ReleaseSockEvent (int /*<<< orphan*/ *) ; 
 scalar_t__ SOCK_LATER ; 
 int /*<<< orphan*/  SeekBuf (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SendTo (TYPE_1__*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StrToIP (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ Tick64 () ; 
 int /*<<< orphan*/  UDP_NAT_TRAVERSAL_VERSION ; 
 scalar_t__ UDP_NAT_T_CONNECT_INTERVAL ; 
 scalar_t__ UDP_NAT_T_PORT ; 
 int /*<<< orphan*/  WaitSockEvent (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  WriteBuf (TYPE_2__*,int /*<<< orphan*/ *,scalar_t__) ; 

SOCK *NewRUDPClientNatT(char *svc_name, IP *ip, UINT *error_code, UINT timeout, bool *cancel, char *hint_str, char *target_hostname)
{
	IP nat_t_ip;
	UINT dummy_int = 0;
	UINT64 giveup_tick;
	bool dummy_bool = false;
	SOCK_EVENT *sock_event;
	SOCK *sock;
	bool same_lan = false;
	char hostname[MAX_SIZE];



	if (timeout == 0)
	{
		timeout = RUDP_TIMEOUT;
	}
	if (error_code == NULL)
	{
		error_code = &dummy_int;
	}
	if (cancel == NULL)
	{
		cancel = &dummy_bool;
	}
	*error_code = RUDP_ERROR_UNKNOWN;
	if (svc_name == NULL || ip == NULL)
	{
		return NULL;
	}

	ListenTcpForPopupFirewallDialog();

	giveup_tick = Tick64() + (UINT64)timeout;

	// Get the IP address of the NAT-T server
	RUDPGetRegisterHostNameByIP(hostname, sizeof(hostname), ip);
	if (GetIP4Ex(&nat_t_ip, hostname, 0, cancel) == false)
	{
		*error_code = RUDP_ERROR_NAT_T_NO_RESPONSE;
		return NULL;
	}

	if (Tick64() >= giveup_tick)
	{
		*error_code = RUDP_ERROR_TIMEOUT;
		return NULL;
	}
	if (*cancel)
	{
		*error_code = RUDP_ERROR_USER_CANCELED;
		return NULL;
	}

	sock = NewUDP4ForSpecificIp(&nat_t_ip, 0);
	if (sock == NULL)
	{
		*error_code = RUDP_ERROR_UNKNOWN;
		return NULL;
	}
	else
	{
		UINT64 next_send_request_tick = 0;
		INTERRUPT_MANAGER *interrupt = NewInterruptManager();
		UINT64 tran_id = Rand64();
		UINT tmp_size = 65536;
		UCHAR *tmp = Malloc(tmp_size);
		char result_ip_str[MAX_SIZE];
		IP result_ip;
		UINT result_port;
		SOCK *ret = NULL;
		UINT num_tries = 0;
		UINT64 current_cookie = 0;

		AddInterrupt(interrupt, giveup_tick);

		sock_event = NewSockEvent();
		JoinSockToSockEvent(sock, sock_event);

		// Communication with the NAT-T server
		while (true)
		{
			UINT64 now = Tick64();
			UINT interval;
			UINT r;
			IP src_ip;
			UINT src_port;
			UINT err;
			UINT num_ignore_errors = 0;

			if (now >= giveup_tick)
			{
				// Time-out
LABEL_TIMEOUT:
				*error_code = RUDP_ERROR_NAT_T_NO_RESPONSE;
				break;
			}

			if (*cancel)
			{
				// User canceled
				*error_code = RUDP_ERROR_USER_CANCELED;
				break;
			}

			err = INFINITE;

			// Receive a response packet from the NAT-T server
			while (err == INFINITE)
			{
				r = RecvFrom(sock, &src_ip, &src_port, tmp, tmp_size);
				if (r == SOCK_LATER)
				{
					// No packet
					break;
				}
				else if (r == 0)
				{
					if (sock->IgnoreRecvErr == false)
					{
						// Communication error
						goto LABEL_TIMEOUT;
					}
					else
					{
						if ((num_ignore_errors++) >= MAX_NUM_IGNORE_ERRORS)
						{
							goto LABEL_TIMEOUT;
						}
					}
				}
				else
				{
					// Check the source IP address and the port number
					if (CmpIpAddr(&src_ip, &nat_t_ip) == 0 && src_port == UDP_NAT_T_PORT)
					{
						BUF *b = NewBuf();
						PACK *p;

						WriteBuf(b, tmp, r);
						SeekBuf(b, 0, 0);


						p = BufToPack(b);

						if (p != NULL)
						{
							UINT64 cookie = PackGetInt64(p, "cookie");
							if (cookie != 0)
							{
								current_cookie = cookie;
							}

							// Compare tran_id
							if (PackGetInt64(p, "tran_id") == tran_id)
							{
								// Compare opcode
								if (PackCmpStr(p, "opcode", "nat_t_connect_request"))
								{
									bool ok = PackGetBool(p, "ok");
									bool multi_candidate = PackGetBool(p, "multi_candidates");

									if (ok)
									{
										// Success
										PackGetStr(p, "result_ip", result_ip_str, sizeof(result_ip_str));
										StrToIP(&result_ip, result_ip_str);

										result_port = PackGetInt(p, "result_port");

										same_lan = PackGetBool(p, "same_lan");

										if (result_port != 0)
										{
											if (IsZeroIp(&result_ip) == false)
											{
												if ((sock->IPv6 == false && IsIP4(&result_ip)) ||
													(sock->IPv6 && IsIP6(&result_ip)))
												{
													err = RUDP_ERROR_OK;
												}
											}
										}
									}
									else if (multi_candidate)
									{
										// There are two or more computers behind the specified IP address
										err = RUDP_ERROR_NAT_T_TWO_OR_MORE;
									}
									else
									{
										// Failure
										err = RUDP_ERROR_NAT_T_NOT_FOUND;
									}
								}
							}

							FreePack(p);
						}

						FreeBuf(b);
					}
				}
			}

			if (err != INFINITE)
			{
				*error_code = err;
				break;
			}

			if (next_send_request_tick == 0 || now >= next_send_request_tick)
			{
				// Send a connection request to the NAT-T server
				BUF *b;
				char ip_str[MAX_SIZE];
				PACK *p = NewPack();

				PackAddStr(p, "opcode", "nat_t_connect_request");
				PackAddInt64(p, "tran_id", tran_id);
				IPToStr(ip_str, sizeof(ip_str), ip);
				PackAddStr(p, "dest_ip", ip_str);
				PackAddInt64(p, "cookie", current_cookie);
				if (IsEmptyStr(hint_str) == false)
				{
					PackAddStr(p, "hint", hint_str);
				}
				if (IsEmptyStr(target_hostname) == false)
				{
					PackAddStr(p, "target_hostname", target_hostname);
				}
				PackAddStr(p, "svc_name", svc_name);

				PackAddInt(p, "nat_traversal_version", UDP_NAT_TRAVERSAL_VERSION);

				b = PackToBuf(p);
				FreePack(p);

				SendTo(sock, &nat_t_ip, UDP_NAT_T_PORT, b->Buf, b->Size);
				FreeBuf(b);

				// Determine the next transmission time
				next_send_request_tick = now + (UINT64)UDP_NAT_T_CONNECT_INTERVAL * (UINT64)(Power(2, MAX(num_tries, 6)));
				num_tries++;
				AddInterrupt(interrupt, next_send_request_tick);
			}

			interval = GetNextIntervalForInterrupt(interrupt);
			interval = MIN(interval, 50);

			WaitSockEvent(sock_event, interval);
		}

		Free(tmp);
		FreeInterruptManager(interrupt);

		if (*error_code == RUDP_ERROR_OK)
		{
			UINT remain_timeout;
			UINT64 now = Tick64();
			// Success to get the IP address and the port number of the target

			// Get the rest timeout tolerance
			if (now <= giveup_tick)
			{
				remain_timeout = (UINT)(giveup_tick - now);
			}
			else
			{
				remain_timeout = 0;
			}

			remain_timeout = MAX(remain_timeout, 2000);

			if (same_lan)
			{
				// Discard current UDP socket and create a new UDP socket in NewRUDPClientDirect().
				// Because using a UDP socket which used for communication with the NAT-T server
				// can cause trouble when the client and the server exists in the same LAN.
				ReleaseSockEvent(sock_event);
				ReleaseSock(sock);

				sock = NULL;
				sock_event = NULL;
			}

			ret = NewRUDPClientDirect(svc_name, &result_ip, result_port, error_code, remain_timeout, cancel,
				sock, sock_event, 0, false);
		}

		if (sock_event != NULL)
		{
			ReleaseSockEvent(sock_event);
		}

		if (sock != NULL)
		{
			if (ret == NULL)
			{
				Disconnect(sock);
			}

			ReleaseSock(sock);
		}

		return ret;
	}
}