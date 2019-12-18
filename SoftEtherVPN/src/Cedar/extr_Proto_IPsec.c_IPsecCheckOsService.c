#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int Check_LastEnabledStatus; int HostIPAddressListChanged; int OsServiceStoped; int /*<<< orphan*/ * Win7; } ;
struct TYPE_6__ {scalar_t__ L2TP_IPsec; scalar_t__ EtherIP_IPsec; } ;
typedef  TYPE_1__ IPSEC_SERVICES ;
typedef  TYPE_2__ IPSEC_SERVER ;

/* Variables and functions */
 int /*<<< orphan*/  IPsecServerGetServices (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  IPsecWin7Free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * IPsecWin7Init () ; 
 int /*<<< orphan*/  IPsecWin7UpdateHostIPAddressList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MsStartIPsecService () ; 
 scalar_t__ MsStopIPsecService () ; 
 int /*<<< orphan*/  UnixSetEnableKernelEspProcessing (int) ; 

bool IPsecCheckOsService(IPSEC_SERVER *s)
{
	bool b_ipsec;
	IPSEC_SERVICES sl;
	bool ret = false;
	// Validate arguments
	if (s == NULL)
	{
		return false;
	}

	IPsecServerGetServices(s, &sl);

	b_ipsec = (sl.EtherIP_IPsec || sl.L2TP_IPsec);

	if (b_ipsec != s->Check_LastEnabledStatus)
	{
		s->Check_LastEnabledStatus = b_ipsec;

		if (b_ipsec)
		{
			// Use of IPsec has been started
#ifdef	OS_WIN32
			if (s->Win7 == NULL)
			{
				s->Win7 = IPsecWin7Init();
				s->HostIPAddressListChanged = true;
			}

			s->OsServiceStoped = false;
#else	// OS_WIN32
#endif	// OS_WIN32
		}
		else
		{
			// Use of IPsec is stopped
#ifdef	OS_WIN32
			if (s->Win7 != NULL)
			{
				IPsecWin7Free(s->Win7);
				s->Win7 = NULL;
			}

			if (s->OsServiceStoped)
			{
				MsStartIPsecService();
				s->OsServiceStoped = false;
			}
#else	// OS_WIN32
			UnixSetEnableKernelEspProcessing(true);
#endif	// OS_WIN32
		}
	}

	if (b_ipsec)
	{
#ifdef	OS_WIN32
		if (MsStopIPsecService())
		{
			s->OsServiceStoped = true;
			ret = true;
		}
#else	// OS_WIN32
		UnixSetEnableKernelEspProcessing(false);
#endif	// OS_WIN32
	}

#ifdef	OS_WIN32
	if (s->Win7 != NULL)
	{
		IPsecWin7UpdateHostIPAddressList(s->Win7);
		s->HostIPAddressListChanged = false;
	}
#endif	// OS_WIN32

	return ret;
}