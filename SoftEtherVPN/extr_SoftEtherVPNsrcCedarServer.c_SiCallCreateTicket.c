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
typedef  int /*<<< orphan*/  user_name_upper ;
typedef  int /*<<< orphan*/  ticket_str ;
typedef  int /*<<< orphan*/  name ;
typedef  int /*<<< orphan*/  hub_name_upper ;
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_7__ {int /*<<< orphan*/  NumSessions; scalar_t__ Point; int /*<<< orphan*/  hostname; } ;
struct TYPE_6__ {int /*<<< orphan*/  Cedar; } ;
typedef  TYPE_1__ SERVER ;
typedef  int /*<<< orphan*/  POLICY ;
typedef  int /*<<< orphan*/  PACK ;
typedef  TYPE_2__ FARM_MEMBER ;

/* Variables and functions */
 int /*<<< orphan*/  BinToStr (char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Format (char*,int,char*,char*,scalar_t__) ; 
 int /*<<< orphan*/  FreePack (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MAX_SESSION_NAME_LEN ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/  MAX_USERNAME_LEN ; 
 int /*<<< orphan*/ * NewPack () ; 
 int /*<<< orphan*/  OutRpcPolicy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PackAddData (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddStr (int /*<<< orphan*/ *,char*,char*) ; 
 scalar_t__ PackGetInt (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  SHA1_SIZE ; 
 int /*<<< orphan*/  SLog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,char*,char*,char*,char*) ; 
 int /*<<< orphan*/ * SiCallTask (TYPE_2__*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  StrCpy (char*,int,char*) ; 
 int /*<<< orphan*/  StrUpper (char*) ; 

void SiCallCreateTicket(SERVER *s, FARM_MEMBER *f, char *hubname, char *username, char *realusername, POLICY *policy, UCHAR *ticket, UINT counter, char *groupname)
{
	PACK *p;
	char name[MAX_SESSION_NAME_LEN + 1];
	char hub_name_upper[MAX_SIZE];
	char user_name_upper[MAX_USERNAME_LEN + 1];
	char ticket_str[MAX_SIZE];
	UINT point;
	// Validate arguments
	if (s == NULL || f == NULL || realusername == NULL || hubname == NULL || username == NULL || policy == NULL || ticket == NULL)
	{
		return;
	}
	if (groupname == NULL)
	{
		groupname = "";
	}

	p = NewPack();
	PackAddStr(p, "HubName", hubname);
	PackAddStr(p, "UserName", username);
	PackAddStr(p, "groupname", groupname);
	PackAddStr(p, "RealUserName", realusername);
	OutRpcPolicy(p, policy);
	PackAddData(p, "Ticket", ticket, SHA1_SIZE);

	BinToStr(ticket_str, sizeof(ticket_str), ticket, SHA1_SIZE);

	StrCpy(hub_name_upper, sizeof(hub_name_upper), hubname);
	StrUpper(hub_name_upper);
	StrCpy(user_name_upper, sizeof(user_name_upper), username);
	StrUpper(user_name_upper);
	Format(name, sizeof(name), "SID-%s-%u", user_name_upper,
		counter);
	PackAddStr(p, "SessionName", name);

	p = SiCallTask(f, p, "createticket");

	SLog(s->Cedar, "LS_TICKET_1", f->hostname, hubname, username, realusername, name, ticket_str);

	point = PackGetInt(p, "Point");
	if (point != 0)
	{
		f->Point = point;
		f->NumSessions++;
	}

	FreePack(p);
}