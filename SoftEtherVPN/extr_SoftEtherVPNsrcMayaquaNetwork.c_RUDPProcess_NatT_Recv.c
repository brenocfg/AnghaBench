#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  new_hostname ;
typedef  int /*<<< orphan*/  myip ;
typedef  int /*<<< orphan*/  client_ip_str ;
typedef  scalar_t__ UINT64 ;
typedef  scalar_t__ UINT ;
struct TYPE_7__ {int Size; int /*<<< orphan*/  Data; } ;
typedef  TYPE_1__ UDPPACKET ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_8__ {char* NatT_Registered_IPAndPort; int NatT_Token_Ok; char* NatT_Token; int NatT_Register_Ok; scalar_t__ NatT_TranId; scalar_t__ Now; char* CurrentRegisterHostname; scalar_t__ NumChangedHostname; scalar_t__ NumChangedHostnameValueResetTick; char NatT_IP; int NatT_EnableSourceIpValidation; scalar_t__ NatT_SessionKey; scalar_t__ NatT_RegisterNextTick; int /*<<< orphan*/  Interrupt; scalar_t__* NatTGlobalUdpPort; scalar_t__ NatT_RegisterFailNum; scalar_t__ NatT_GetTokenNextTick; int /*<<< orphan*/  Lock; int /*<<< orphan*/  HaltEvent; scalar_t__ NatT_GetTokenFailNum; scalar_t__ ServerMode; } ;
typedef  TYPE_2__ RUDP_STACK ;
typedef  int /*<<< orphan*/  PACK ;
typedef  int /*<<< orphan*/  IP ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int /*<<< orphan*/  AddInterrupt (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/ * BufToPack (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ClearStr (char*,int) ; 
 int /*<<< orphan*/  Copy (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Debug (char*,...) ; 
 int /*<<< orphan*/  ExtractAndApplyDynList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeBuf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreePack (int /*<<< orphan*/ *) ; 
 scalar_t__ GenRandInterval (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int IsEmptyStr (char*) ; 
 int IsZeroIp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/  MIN (int,int) ; 
 int /*<<< orphan*/ * Malloc (scalar_t__) ; 
 int /*<<< orphan*/ * NewBuf () ; 
 scalar_t__ PackCmpStr (int /*<<< orphan*/ *,char*,char*) ; 
 void* PackGetBool (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ PackGetInt (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ PackGetInt64 (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ PackGetStr (int /*<<< orphan*/ *,char*,char*,int) ; 
 int /*<<< orphan*/  RUDPAddIpToValidateList (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RUDPGetRegisterHostNameByIP (char*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ RUDPParseIPAndPortStr (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  RUDPSendPacket (TYPE_2__*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ RUDP_NATT_CONT_CHANGE_HOSTNAME_RESET_INTERVAL ; 
 scalar_t__ RUDP_NATT_MAX_CONT_CHANGE_HOSTNAME ; 
 int /*<<< orphan*/  Rand (int /*<<< orphan*/ *,scalar_t__) ; 
 int Rand32 () ; 
 int /*<<< orphan*/  SeekBuf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetCurrentGlobalIP (int /*<<< orphan*/ *,int) ; 
 scalar_t__ StartWith (char*,char*) ; 
 scalar_t__ StrCmpi (char*,char*) ; 
 int /*<<< orphan*/  StrCpy (char*,int,char*) ; 
 int /*<<< orphan*/  StrToIP (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  UDP_NAT_T_GET_TOKEN_INTERVAL_2_MAX ; 
 int /*<<< orphan*/  UDP_NAT_T_GET_TOKEN_INTERVAL_2_MIN ; 
 int /*<<< orphan*/  UDP_NAT_T_REGISTER_INTERVAL_MAX ; 
 int /*<<< orphan*/  UDP_NAT_T_REGISTER_INTERVAL_MIN ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WriteBuf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Zero (char*,int) ; 
 int g_source_ip_validation_force_disable ; 

void RUDPProcess_NatT_Recv(RUDP_STACK *r, UDPPACKET *udp)
{
	BUF *b;
	PACK *p;
	// Validate arguments
	if (r == NULL || udp == NULL)
	{
		return;
	}

	if (udp->Size >= 8)
	{
		char tmp[128];

		Zero(tmp, sizeof(tmp));
		Copy(tmp, udp->Data, MIN(udp->Size, sizeof(tmp) - 1));

		if (StartWith(tmp, "IP="))
		{
			IP my_ip;
			UINT my_port;

			// There was a response to the packet to determine the NAT state
			if (IsEmptyStr(r->NatT_Registered_IPAndPort) == false)
			{
				if (StrCmpi(r->NatT_Registered_IPAndPort, tmp) != 0)
				{
					// Redo getting the token and registration because the NAT state is changed
					ClearStr(r->NatT_Registered_IPAndPort, sizeof(r->NatT_Registered_IPAndPort));

					r->NatT_GetTokenNextTick = 0;
					r->NatT_GetTokenFailNum = 0;
					r->NatT_Token_Ok = false;
					Zero(r->NatT_Token, sizeof(r->NatT_Token));

					r->NatT_RegisterNextTick = 0;
					r->NatT_RegisterFailNum = 0;
					r->NatT_Register_Ok = false;
				}
			}

			if (RUDPParseIPAndPortStr(udp->Data, udp->Size, &my_ip, &my_port))
			{
				if (r->NatTGlobalUdpPort != NULL)
				{
					*r->NatTGlobalUdpPort = my_port;
				}
			}

			return;
		}
	}

	// Interpret the UDP packet
	b = NewBuf();
	WriteBuf(b, udp->Data, udp->Size);
	SeekBuf(b, 0, 0);

	p = BufToPack(b);

	if (p != NULL)
	{
		bool is_ok = PackGetBool(p, "ok");
		UINT64 tran_id = PackGetInt64(p, "tran_id");

		ExtractAndApplyDynList(p);

		if (r->ServerMode)
		{
			if (PackCmpStr(p, "opcode", "get_token"))
			{
				// Get the Token
				if (is_ok && (tran_id == r->NatT_TranId))
				{
					char tmp[MAX_SIZE];

					if (PackGetStr(p, "token", tmp, sizeof(tmp)) && IsEmptyStr(tmp) == false)
					{
						char myip[MAX_SIZE];
						// Acquisition success
						StrCpy(r->NatT_Token, sizeof(r->NatT_Token), tmp);
						r->NatT_Token_Ok = true;
						r->NatT_GetTokenNextTick = r->Now + (UINT64)GenRandInterval(UDP_NAT_T_GET_TOKEN_INTERVAL_2_MIN, UDP_NAT_T_GET_TOKEN_INTERVAL_2_MAX);
						r->NatT_GetTokenFailNum = 0;

						// Since success to obtain the self global IPv4 address,
						// re-obtain the destination NAT-T host from this IPv4 address
						if (PackGetStr(p, "your_ip", myip, sizeof(myip)))
						{
							IP ip;
							char new_hostname[MAX_SIZE];

							StrToIP(&ip, myip);

							SetCurrentGlobalIP(&ip, false);

							RUDPGetRegisterHostNameByIP(new_hostname,
								sizeof(new_hostname), &ip);

							Lock(r->Lock);
							{
								if (StrCmpi(r->CurrentRegisterHostname, new_hostname) != 0)
								{
									r->NumChangedHostname++;

									if (r->NumChangedHostname <= RUDP_NATT_MAX_CONT_CHANGE_HOSTNAME)
									{
										if (r->NumChangedHostnameValueResetTick == 0)
										{
											r->NumChangedHostnameValueResetTick = r->Now + (UINT64)RUDP_NATT_CONT_CHANGE_HOSTNAME_RESET_INTERVAL;
										}

										// Change the host name
										Debug("CurrentRegisterHostname Changed: New=%s\n", new_hostname);
										StrCpy(r->CurrentRegisterHostname, sizeof(r->CurrentRegisterHostname), new_hostname);

										Zero(&r->NatT_IP, sizeof(r->NatT_IP));
										//Zero(&r->NatT_IP_Safe, sizeof(r->NatT_IP_Safe));

										Set(r->HaltEvent);
									}
									else
									{
										if (r->NumChangedHostnameValueResetTick == 0)
										{
											r->NumChangedHostnameValueResetTick = r->Now + (UINT64)RUDP_NATT_CONT_CHANGE_HOSTNAME_RESET_INTERVAL;
										}

										if (r->Now >= r->NumChangedHostnameValueResetTick)
										{
											r->NumChangedHostname = 0;
											r->NumChangedHostnameValueResetTick = 0;
										}
									}
								}
								else
								{
									r->NumChangedHostname = 0;
									r->NumChangedHostnameValueResetTick = 0;
								}
							}
							Unlock(r->Lock);
						}

						AddInterrupt(r->Interrupt, r->NatT_GetTokenNextTick);
					}
				}
			}
			else if (PackCmpStr(p, "opcode", "nat_t_register"))
			{
				// NAT-T server registration result
				if (is_ok && (tran_id == r->NatT_TranId))
				{
					UINT my_global_port;
					// Successful registration
					r->NatT_Register_Ok = true;
					r->NatT_RegisterNextTick = r->Now + (UINT64)GenRandInterval(UDP_NAT_T_REGISTER_INTERVAL_MIN, UDP_NAT_T_REGISTER_INTERVAL_MAX);
					r->NatT_RegisterFailNum = 0;

					Debug("NAT-T Registered.\n");

					// Save the IP address and port number at the time of registration
					PackGetStr(p, "your_ip_and_port", r->NatT_Registered_IPAndPort, sizeof(r->NatT_Registered_IPAndPort));

					if (g_source_ip_validation_force_disable == false)
					{
						// Enable the source IP address validation mechanism
						r->NatT_EnableSourceIpValidation = PackGetBool(p, "enable_source_ip_validation");

					}
					else
					{
						// Force disable the source IP address validation mechanism
						r->NatT_EnableSourceIpValidation = false;
					}

					// Global port of itself
					my_global_port = PackGetInt(p, "your_port");

					if (my_global_port != 0)
					{
						if (r->NatTGlobalUdpPort != NULL)
						{
							*r->NatTGlobalUdpPort = my_global_port;
						}
					}

					AddInterrupt(r->Interrupt, r->NatT_RegisterNextTick);
				}
			}
			else if (PackCmpStr(p, "opcode", "nat_t_connect_relay"))
			{
				// Connection request from the client via the NAT-T server
				if (is_ok && (PackGetInt64(p, "session_key") == r->NatT_SessionKey))
				{
					char client_ip_str[MAX_SIZE];
					UINT client_port;
					IP client_ip;

					PackGetStr(p, "client_ip", client_ip_str, sizeof(client_ip_str));
					client_port = PackGetInt(p, "client_port");
					StrToIP(&client_ip, client_ip_str);

					if (IsZeroIp(&client_ip) == false && client_port != 0)
					{
						UCHAR *rand_data;
						UINT rand_size;

						if (r->NatT_EnableSourceIpValidation)
						{
							RUDPAddIpToValidateList(r, &client_ip);
						}

						rand_size = Rand32() % 19;
						rand_data = Malloc(rand_size);

						Rand(rand_data, rand_size);

						RUDPSendPacket(r, &client_ip, client_port, rand_data, rand_size, 0);

						Free(rand_data);
					}
				}
			}
		}

		FreePack(p);
	}

	FreeBuf(b);
}