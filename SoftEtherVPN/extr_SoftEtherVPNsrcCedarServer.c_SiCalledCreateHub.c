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
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  o ;
typedef  int /*<<< orphan*/  name ;
typedef  int /*<<< orphan*/  log ;
typedef  int VH_OPTION ;
typedef  int UINT ;
struct TYPE_18__ {int Type; int FarmMember_MaxSessionClientBridgeApply; int Offline; int /*<<< orphan*/  SecureNATOption; int /*<<< orphan*/  HashedPassword; int /*<<< orphan*/  SecurePassword; void* FarmMember_MaxSessionBridge; void* FarmMember_MaxSessionClient; scalar_t__ CreatedTime; scalar_t__ LastLoginTime; scalar_t__ LastCommTime; } ;
struct TYPE_17__ {int SavePacketLog; int PacketLogSwitchType; int SaveSecurityLog; int SecurityLogSwitchType; int /*<<< orphan*/  PacketLogConfig; void* MaxSession; } ;
struct TYPE_16__ {int /*<<< orphan*/  Cedar; } ;
typedef  TYPE_1__ SERVER ;
typedef  int /*<<< orphan*/  PACK ;
typedef  TYPE_2__ HUB_OPTION ;
typedef  TYPE_2__ HUB_LOG ;
typedef  TYPE_4__ HUB ;
typedef  int /*<<< orphan*/  ACCESS ;

/* Variables and functions */
 int /*<<< orphan*/  AddAccessList (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AddHub (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  Debug (char*) ; 
 int /*<<< orphan*/  EnableSecureNAT (TYPE_4__*,int) ; 
 int /*<<< orphan*/  Free (int /*<<< orphan*/ *) ; 
 void* INFINITE ; 
 int /*<<< orphan*/  InVhOption (int*,int /*<<< orphan*/ *) ; 
 int MAX_SIZE ; 
 int NUM_PACKET_LOG ; 
 TYPE_4__* NewHub (int /*<<< orphan*/ ,char*,TYPE_2__*) ; 
 int PackGetBool (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PackGetData2 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* PackGetInt (int /*<<< orphan*/ *,char*) ; 
 int PackGetIntEx (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  PackGetStr (int /*<<< orphan*/ *,char*,char*,int) ; 
 int /*<<< orphan*/  ReleaseHub (TYPE_4__*) ; 
 int /*<<< orphan*/  SHA1_SIZE ; 
 int /*<<< orphan*/  SetHubLogSetting (TYPE_4__*,TYPE_2__*) ; 
 int /*<<< orphan*/  SetHubOnline (TYPE_4__*) ; 
 int SiNumAccessFromPack (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SiPackToAccess (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  Zero (TYPE_2__*,int) ; 

void SiCalledCreateHub(SERVER *s, PACK *p)
{
	char name[MAX_SIZE];
	UINT type;
	HUB_OPTION o;
	HUB_LOG log;
	bool save_packet_log;
	UINT packet_log_switch_type;
	UINT packet_log_config[NUM_PACKET_LOG];
	bool save_security_log;
	UINT security_log_switch_type;
	UINT i;
	HUB *h;
	// Validate arguments
	if (s == NULL || p == NULL)
	{
		return;
	}

	PackGetStr(p, "HubName", name, sizeof(name));
	type = PackGetInt(p, "HubType");
	Zero(&o, sizeof(o));
	o.MaxSession = PackGetInt(p, "MaxSession");
	save_packet_log = PackGetInt(p, "SavePacketLog");
	packet_log_switch_type = PackGetInt(p, "PacketLogSwitchType");
	for (i = 0;i < NUM_PACKET_LOG;i++)
	{
		packet_log_config[i] = PackGetIntEx(p, "PacketLogConfig", i);
	}
	save_security_log = PackGetInt(p, "SaveSecurityLog");
	security_log_switch_type = PackGetInt(p, "SecurityLogSwitchType");

	Zero(&log, sizeof(log));
	log.SavePacketLog = save_packet_log;
	log.PacketLogSwitchType = packet_log_switch_type;
	Copy(log.PacketLogConfig, packet_log_config, sizeof(log.PacketLogConfig));
	log.SaveSecurityLog = save_security_log;
	log.SecurityLogSwitchType = security_log_switch_type;

	h = NewHub(s->Cedar, name, &o);
	h->LastCommTime = h->LastLoginTime = h->CreatedTime = 0;
	SetHubLogSetting(h, &log);
	h->Type = type;
	h->FarmMember_MaxSessionClient = PackGetInt(p, "MaxSessionClient");
	h->FarmMember_MaxSessionBridge = PackGetInt(p, "MaxSessionBridge");
	h->FarmMember_MaxSessionClientBridgeApply = PackGetBool(p, "MaxSessionClientBridgeApply");

	if (h->FarmMember_MaxSessionClientBridgeApply == false)
	{
		h->FarmMember_MaxSessionClient = INFINITE;
		h->FarmMember_MaxSessionBridge = INFINITE;
	}

	PackGetData2(p, "SecurePassword", h->SecurePassword, SHA1_SIZE);
	PackGetData2(p, "HashedPassword", h->HashedPassword, SHA1_SIZE);

	for (i = 0;i < SiNumAccessFromPack(p);i++)
	{
		ACCESS *a = SiPackToAccess(p, i);
		AddAccessList(h, a);
		Free(a);
	}

	if (PackGetBool(p, "EnableSecureNAT"))
	{
		VH_OPTION t;

		InVhOption(&t, p);

		Copy(h->SecureNATOption, &t, sizeof(VH_OPTION));
		EnableSecureNAT(h, true);

		Debug("SiCalledCreateHub: SecureNAT Created.\n");
	}

	AddHub(s->Cedar, h);
	h->Offline = true;
	SetHubOnline(h);

	ReleaseHub(h);
}