#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
struct TYPE_4__ {int /*<<< orphan*/  Traffic; int /*<<< orphan*/ * Policy; void* UpdatedTime; void* CreatedTime; void* AuthData; scalar_t__ AuthType; int /*<<< orphan*/ * Group; int /*<<< orphan*/ * GroupName; void* Note; void* RealName; int /*<<< orphan*/  Name; int /*<<< orphan*/  ref; int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ USER ;
typedef  scalar_t__ UINT ;

/* Variables and functions */
 scalar_t__ AUTHTYPE_ANONYMOUS ; 
 int /*<<< orphan*/  CopyStr (char*) ; 
 void* CopyUniStr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NewLock () ; 
 int /*<<< orphan*/  NewRef () ; 
 int /*<<< orphan*/  NewTraffic () ; 
 void* SystemTime64 () ; 
 TYPE_1__* ZeroMalloc (int) ; 

USER *NewUser(char *name, wchar_t *realname, wchar_t *note, UINT authtype, void *authdata)
{
	USER *u;
	// Validate arguments
	if (name == NULL || realname == NULL || note == NULL)
	{
		return NULL;
	}
	if (authtype != AUTHTYPE_ANONYMOUS && authdata == NULL)
	{
		return NULL;
	}

	u = ZeroMalloc(sizeof(USER));
	u->lock = NewLock();
	u->ref = NewRef();
	u->Name = CopyStr(name);
	u->RealName = CopyUniStr(realname);
	u->Note = CopyUniStr(note);
	u->GroupName = NULL;
	u->Group = NULL;
	u->AuthType = authtype;
	u->AuthData = authdata;
	u->CreatedTime = SystemTime64();
	u->UpdatedTime = SystemTime64();

	u->Policy = NULL;
	u->Traffic = NewTraffic();

	return u;
}