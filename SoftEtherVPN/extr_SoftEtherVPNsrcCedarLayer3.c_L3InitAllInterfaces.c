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
typedef  scalar_t__ UINT ;
struct TYPE_8__ {int /*<<< orphan*/  HubName; int /*<<< orphan*/  Hub; } ;
struct TYPE_7__ {int /*<<< orphan*/  Cedar; int /*<<< orphan*/  IfList; } ;
typedef  int /*<<< orphan*/  THREAD ;
typedef  TYPE_1__ L3SW ;
typedef  TYPE_2__ L3IF ;

/* Variables and functions */
 int /*<<< orphan*/  GetHub (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  L3IfThread ; 
 int /*<<< orphan*/  L3InitInterface (TYPE_2__*) ; 
 TYPE_2__* LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * NewThread (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  ReleaseThread (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WaitThreadInit (int /*<<< orphan*/ *) ; 

void L3InitAllInterfaces(L3SW *s)
{
	UINT i;
	// Validate arguments
	if (s == NULL)
	{
		return;
	}

	for (i = 0;i < LIST_NUM(s->IfList);i++)
	{
		L3IF *f = LIST_DATA(s->IfList, i);
		THREAD *t;

		L3InitInterface(f);

		f->Hub = GetHub(s->Cedar, f->HubName);
		t = NewThread(L3IfThread, f);
		WaitThreadInit(t);
		ReleaseThread(t);
	}
}