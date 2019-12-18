#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
struct TYPE_18__ {int /*<<< orphan*/  OsServiceCheckThreadEvent; int /*<<< orphan*/  LockSettings; TYPE_3__* Ike; TYPE_10__* UdpListener; TYPE_2__* Cedar; int /*<<< orphan*/  Services; scalar_t__ NoMoreChangeSettings; } ;
struct TYPE_17__ {int /*<<< orphan*/  IPsec_Secret; scalar_t__ EtherIP_IPsec; scalar_t__ L2TP_IPsec; scalar_t__ L2TP_Raw; } ;
struct TYPE_16__ {int /*<<< orphan*/  Secret; } ;
struct TYPE_15__ {TYPE_1__* Server; } ;
struct TYPE_14__ {TYPE_4__ ListenIP; } ;
struct TYPE_13__ {int /*<<< orphan*/  ListenIP; } ;
typedef  TYPE_4__ IPSEC_SERVICES ;
typedef  TYPE_5__ IPSEC_SERVER ;
typedef  int /*<<< orphan*/  IP ;

/* Variables and functions */
 int /*<<< orphan*/  AddPortToUdpListener (TYPE_10__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,TYPE_4__*,int) ; 
 int /*<<< orphan*/  DeletePortFromUdpListener (TYPE_10__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPSEC_PORT_IPSEC_ESP_RAW ; 
 int /*<<< orphan*/  IPSEC_PORT_IPSEC_ESP_RAW_WPF ; 
 int /*<<< orphan*/  IPSEC_PORT_IPSEC_ESP_UDP ; 
 int /*<<< orphan*/  IPSEC_PORT_IPSEC_ISAKMP ; 
 int /*<<< orphan*/  IPSEC_PORT_L2TP ; 
 int /*<<< orphan*/  IPsecNormalizeServiceSetting (TYPE_5__*) ; 
 int IsEmptyStr (int /*<<< orphan*/ ) ; 
 int IsZero (TYPE_4__*,int) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 

void IPsecServerSetServices(IPSEC_SERVER *s, IPSEC_SERVICES *sl)
{
	// Validate arguments
	if (s == NULL || sl == NULL)
	{
		return;
	}

	if (IsZero(sl, sizeof(IPSEC_SERVICES)) == false)
	{
		if (s->NoMoreChangeSettings)
		{
			return;
		}
	}

	Lock(s->LockSettings);
	{
		Copy(&s->Services, sl, sizeof(IPSEC_SERVICES));

		Copy(&s->UdpListener->ListenIP, &s->Cedar->Server->ListenIP, sizeof(IP));

		if (sl->L2TP_Raw)
		{
			AddPortToUdpListener(s->UdpListener, IPSEC_PORT_L2TP);
		}
		else
		{
			DeletePortFromUdpListener(s->UdpListener, IPSEC_PORT_L2TP);
		}

		if (sl->L2TP_IPsec || sl->EtherIP_IPsec)
		{
			AddPortToUdpListener(s->UdpListener, IPSEC_PORT_IPSEC_ISAKMP);
			AddPortToUdpListener(s->UdpListener, IPSEC_PORT_IPSEC_ESP_UDP);
			AddPortToUdpListener(s->UdpListener, IPSEC_PORT_IPSEC_ESP_RAW);
			AddPortToUdpListener(s->UdpListener, IPSEC_PORT_IPSEC_ESP_RAW_WPF);
		}
		else
		{
			DeletePortFromUdpListener(s->UdpListener, IPSEC_PORT_IPSEC_ISAKMP);
			DeletePortFromUdpListener(s->UdpListener, IPSEC_PORT_IPSEC_ESP_UDP);
			DeletePortFromUdpListener(s->UdpListener, IPSEC_PORT_IPSEC_ESP_RAW);
			DeletePortFromUdpListener(s->UdpListener, IPSEC_PORT_IPSEC_ESP_RAW_WPF);
		}

		if (IsEmptyStr(sl->IPsec_Secret) == false)
		{
			StrCpy(s->Ike->Secret, sizeof(s->Ike->Secret), sl->IPsec_Secret);
		}

		IPsecNormalizeServiceSetting(s);
	}
	Unlock(s->LockSettings);

	Set(s->OsServiceCheckThreadEvent);
}