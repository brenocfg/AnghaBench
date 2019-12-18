#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  hostname ;
typedef  int UINT64 ;
typedef  scalar_t__ UINT ;
struct TYPE_10__ {int NatT_Halt; int NatT_IP_Changed; int /*<<< orphan*/  NatT_HaltEvent; int /*<<< orphan*/  NatT_Lock; int /*<<< orphan*/  NatT_IP; } ;
typedef  TYPE_1__ UDP_ACCEL ;
struct TYPE_11__ {int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  THREAD ;
typedef  TYPE_2__ IP ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 int /*<<< orphan*/  Debug (char*,char*,char*) ; 
 int GetIP4Ex (TYPE_2__*,char*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  IPToStr (char*,int,TYPE_2__*) ; 
 scalar_t__ IsZeroIP (TYPE_2__*) ; 
 int IsZeroIp (TYPE_2__*) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int MAX_SIZE ; 
 scalar_t__ MIN (int,int) ; 
 int /*<<< orphan*/  RUDPGetRegisterHostNameByIP (char*,int,TYPE_2__*) ; 
 int /*<<< orphan*/  Rand8 () ; 
 int /*<<< orphan*/  SetIP (TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ UDP_NAT_T_GET_IP_INTERVAL ; 
 scalar_t__ UDP_NAT_T_GET_IP_INTERVAL_MAX ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Wait (int /*<<< orphan*/ ,scalar_t__) ; 

void NatT_GetIpThread(THREAD *thread, void *param)
{
	UDP_ACCEL *a;
	char hostname[MAX_SIZE];
	static IP dummy_ip = {0};
	UINT num_retry = 0;
	// Validate arguments
	if (thread == NULL || param == NULL)
	{
		return;
	}

	a = (UDP_ACCEL *)param;

	if (IsZeroIP(&dummy_ip))
	{
		SetIP(&dummy_ip, 11, Rand8(), Rand8(), Rand8());
	}

	RUDPGetRegisterHostNameByIP(hostname, sizeof(hostname), &dummy_ip);

	while (a->NatT_Halt == false)
	{
		IP ip;
		UINT wait_time = UDP_NAT_T_GET_IP_INTERVAL;

		// Get the IP address
		bool ret = GetIP4Ex(&ip, hostname, 0, &a->NatT_Halt);

		if (ret && (IsZeroIp(&ip) == false))
		{
			char tmp[128];

			// Success to get
			Lock(a->NatT_Lock);
			{
				Copy(&a->NatT_IP, &ip, sizeof(IP));
			}
			Unlock(a->NatT_Lock);

			IPToStr(tmp, sizeof(tmp), &ip);
			Debug("NAT-T IP Address Resolved: %s = %s\n", hostname, tmp);

			a->NatT_IP_Changed = true;

			break;
		}

		// Fail to get
		num_retry++;

		wait_time = (UINT)(MIN((UINT64)UDP_NAT_T_GET_IP_INTERVAL * (UINT64)num_retry, (UINT64)UDP_NAT_T_GET_IP_INTERVAL_MAX));

		Wait(a->NatT_HaltEvent, wait_time);
	}
}