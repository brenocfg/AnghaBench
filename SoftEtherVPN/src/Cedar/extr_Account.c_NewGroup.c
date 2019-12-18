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
struct TYPE_4__ {int /*<<< orphan*/  Traffic; int /*<<< orphan*/ * Policy; void* Note; void* RealName; int /*<<< orphan*/  Name; int /*<<< orphan*/  ref; int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ USERGROUP ;

/* Variables and functions */
 int /*<<< orphan*/  CopyStr (char*) ; 
 void* CopyUniStr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NewLock () ; 
 int /*<<< orphan*/  NewRef () ; 
 int /*<<< orphan*/  NewTraffic () ; 
 TYPE_1__* ZeroMalloc (int) ; 

USERGROUP *NewGroup(char *name, wchar_t *realname, wchar_t *note)
{
	USERGROUP *g;
	// Validate arguments
	if (name == NULL || realname == NULL || note == NULL)
	{
		return NULL;
	}

	g = ZeroMalloc(sizeof(USERGROUP));
	g->lock = NewLock();
	g->ref = NewRef();
	g->Name = CopyStr(name);
	g->RealName = CopyUniStr(realname);
	g->Note = CopyUniStr(note);
	g->Policy = NULL;
	g->Traffic = NewTraffic();

	return g;
}