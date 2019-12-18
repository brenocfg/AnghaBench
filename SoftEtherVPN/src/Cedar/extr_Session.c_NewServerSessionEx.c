#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_14__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  user_name_upper ;
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  rand ;
typedef  int /*<<< orphan*/  pc_name ;
typedef  int /*<<< orphan*/  name ;
typedef  int /*<<< orphan*/  machine ;
typedef  int /*<<< orphan*/  hub_name_upper ;
typedef  void* UCHAR ;
struct TYPE_24__ {TYPE_14__* Server; } ;
struct TYPE_23__ {char* InProcPrefix; int /*<<< orphan*/  ref; TYPE_1__* Thread; } ;
struct TYPE_22__ {char* Name; int /*<<< orphan*/  SessionCounter; scalar_t__ IsVgsSuperRelayHub; scalar_t__ IsVgsHub; } ;
struct TYPE_21__ {int ServerMode; int InProcMode; int* IpcMacAddress; int /*<<< orphan*/  UniqueId; int /*<<< orphan*/  SessionKey32; int /*<<< orphan*/  SessionKey; int /*<<< orphan*/ * Policy; int /*<<< orphan*/  Name; TYPE_5__* Connection; int /*<<< orphan*/  PacketAdapter; int /*<<< orphan*/  DelayedPacketList; int /*<<< orphan*/  ClientStatus; TYPE_4__* Hub; TYPE_1__* Thread; int /*<<< orphan*/  QoS; void* OldTraffic; void* TrafficLock; int /*<<< orphan*/  CancelList; int /*<<< orphan*/  Cancel1; int /*<<< orphan*/  HaltEvent; void* Traffic; int /*<<< orphan*/  LastCommTime; int /*<<< orphan*/  CreatedTime; TYPE_6__* Cedar; int /*<<< orphan*/  ref; void* lock; int /*<<< orphan*/  LoggingRecordCount; } ;
struct TYPE_20__ {int NumTokens; char** Token; } ;
struct TYPE_19__ {int /*<<< orphan*/  ref; } ;
struct TYPE_18__ {scalar_t__ ServerType; } ;
typedef  TYPE_2__ TOKEN_LIST ;
typedef  TYPE_3__ SESSION ;
typedef  int /*<<< orphan*/  POLICY ;
typedef  TYPE_4__ HUB ;
typedef  TYPE_5__ CONNECTION ;
typedef  TYPE_6__ CEDAR ;

/* Variables and functions */
 int /*<<< orphan*/  ADMINISTRATOR_USERNAME ; 
 int /*<<< orphan*/  AddRef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AddSession (TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  BRIDGE_USER_NAME ; 
 int /*<<< orphan*/  BinToStr (char*,int,void**,int) ; 
 int /*<<< orphan*/  CLIENT_STATUS_ESTABLISHED ; 
 int /*<<< orphan*/  Copy (int*,void**,int) ; 
 int /*<<< orphan*/  CopyStr (char*) ; 
 int /*<<< orphan*/  Debug (char*,char*) ; 
 int /*<<< orphan*/  Format (char*,int,char*,char*,char*,...) ; 
 int /*<<< orphan*/  FreeToken (TYPE_2__*) ; 
 int /*<<< orphan*/  GetHubPacketAdapter () ; 
 int /*<<< orphan*/  GetMachineName (char*,int) ; 
 int /*<<< orphan*/  GetServerCapsBool (TYPE_14__*,char*) ; 
 int /*<<< orphan*/  Inc (int /*<<< orphan*/ ) ; 
 scalar_t__ IsEmptyStr (char*) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/  MAX_USERNAME_LEN ; 
 int /*<<< orphan*/  MacToStr (char*,int,int*) ; 
 int /*<<< orphan*/  NewCancel () ; 
 int /*<<< orphan*/  NewCancelList () ; 
 int /*<<< orphan*/  NewCounter () ; 
 int /*<<< orphan*/  NewEvent () ; 
 int /*<<< orphan*/  NewList (int /*<<< orphan*/ *) ; 
 void* NewLock () ; 
 int /*<<< orphan*/  NewRef () ; 
 int /*<<< orphan*/  NewSessionKey (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* NewTraffic () ; 
 TYPE_2__* ParseToken (char*,char*) ; 
 int /*<<< orphan*/  Rand (void**,int) ; 
 scalar_t__ SERVER_TYPE_STANDALONE ; 
 int SHA1_SIZE ; 
 int /*<<< orphan*/  Sha0 (void**,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StrCat (char*,int,char*) ; 
 scalar_t__ StrCmpi (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StrCpy (char*,int,char*) ; 
 int /*<<< orphan*/  StrLen (char*) ; 
 int /*<<< orphan*/  StrUpper (char*) ; 
 int /*<<< orphan*/  Tick64 () ; 
 int /*<<< orphan*/  Trim (char*) ; 
 TYPE_3__* ZeroMalloc (int) ; 

SESSION *NewServerSessionEx(CEDAR *cedar, CONNECTION *c, HUB *h, char *username, POLICY *policy, bool inproc_mode, UCHAR *ipc_mac_address)
{
	SESSION *s;
	char name[MAX_SIZE];
	char hub_name_upper[MAX_SIZE];
	char user_name_upper[MAX_USERNAME_LEN + 1];
	// Validate arguments
	if (cedar == NULL || c == NULL || h == NULL || username == NULL || policy == NULL)
	{
		return NULL;
	}

	// Initialize the SESSION object
	s = ZeroMalloc(sizeof(SESSION));

	s->LoggingRecordCount = NewCounter();
	s->lock = NewLock();
	s->ref = NewRef();
	s->Cedar = cedar;
	s->ServerMode = true;
	s->CreatedTime = s->LastCommTime = Tick64();
	s->Traffic = NewTraffic();
	s->HaltEvent = NewEvent();
	s->Cancel1 = NewCancel();
	s->CancelList = NewCancelList();
	s->Thread = c->Thread;
	s->TrafficLock = NewLock();
	s->OldTraffic = NewTraffic();
	s->QoS = GetServerCapsBool(cedar->Server, "b_support_qos");
	AddRef(s->Thread->ref);
	s->Hub = h;
	s->ClientStatus = CLIENT_STATUS_ESTABLISHED;

	// Delayed packet list
	s->DelayedPacketList = NewList(NULL);

	// Packet adapter for the HUB
	s->PacketAdapter = GetHubPacketAdapter();

	s->Connection = c;
	AddRef(c->ref);

	// Determine the new session name
	StrCpy(hub_name_upper, sizeof(hub_name_upper), h->Name);
	StrUpper(hub_name_upper);
	StrCpy(user_name_upper, sizeof(user_name_upper), username);
	StrUpper(user_name_upper);

	if ((StrCmpi(username, ADMINISTRATOR_USERNAME) != 0) && (StrCmpi(username, BRIDGE_USER_NAME) != 0) || (cedar->Server == NULL || cedar->Server->ServerType == SERVER_TYPE_STANDALONE))
	{
		if (IsEmptyStr(c->InProcPrefix))
		{
			Format(name, sizeof(name), "SID-%s-%u", user_name_upper, Inc(h->SessionCounter));
		}
		else
		{
			Format(name, sizeof(name), "SID-%s-[%s]-%u", user_name_upper, c->InProcPrefix, Inc(h->SessionCounter));
		}

		if (h->IsVgsHub || h->IsVgsSuperRelayHub)
		{
			UCHAR rand[5];
			char tmp[32];

			Rand(rand, sizeof(rand));

			BinToStr(tmp, sizeof(tmp), rand, sizeof(rand));

			StrCat(name, sizeof(name), "-");
			StrCat(name, sizeof(name), tmp);
		}
	}
	else
	{
		UCHAR rand[SHA1_SIZE];
		char tmp[MAX_SIZE];
		Rand(rand, sizeof(rand));
		BinToStr(tmp, sizeof(tmp), rand, 3);

		if (StrCmpi(username, BRIDGE_USER_NAME) != 0)
		{
			Format(name, sizeof(name), "SID-%s-%s", user_name_upper,
				tmp);
		}
		else
		{
			char pc_name[MAX_SIZE];
			TOKEN_LIST *t;

			GetMachineName(tmp, sizeof(tmp));
			t = ParseToken(tmp, ".");
			if (t->NumTokens >= 1)
			{
				StrCpy(pc_name, sizeof(pc_name), t->Token[0]);
			}
			else
			{
				StrCpy(pc_name, sizeof(pc_name), "pc");
			}
			FreeToken(t);

			StrUpper(pc_name);

			Format(name, sizeof(name), "SID-%s-%s-%u", user_name_upper, pc_name,
				Inc(h->SessionCounter));
		}
	}

	s->Name = CopyStr(name);
	s->Policy = policy;
	s->InProcMode = inproc_mode;

	// Add a SESSION to the HUB
	AddSession(h, s);

	// Create a key
	NewSessionKey(cedar, s->SessionKey, &s->SessionKey32);

	// Generate a MAC address for IPC
	if (s->InProcMode)
	{
		if (ipc_mac_address != NULL)
		{
			Copy(s->IpcMacAddress, ipc_mac_address, 6);
		}
		else
		{
			char tmp[MAX_SIZE];
			char machine[MAX_SIZE];
			UCHAR hash[SHA1_SIZE];

			GetMachineName(machine, sizeof(machine));

			Format(tmp, sizeof(tmp), "%s@%s@%u", machine, h->Name, s->UniqueId);

			StrUpper(tmp);
			Trim(tmp);

			Sha0(hash, tmp, StrLen(tmp));

			s->IpcMacAddress[0] = 0xCA;
			s->IpcMacAddress[1] = hash[1];
			s->IpcMacAddress[2] = hash[2];
			s->IpcMacAddress[3] = hash[3];
			s->IpcMacAddress[4] = hash[4];
			s->IpcMacAddress[5] = hash[5];

			MacToStr(tmp, sizeof(tmp), s->IpcMacAddress);
			Debug("MAC Address for IPC: %s\n", tmp);
		}
	}

	return s;
}