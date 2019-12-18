#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  void* UINT ;
struct TYPE_5__ {int /*<<< orphan*/  Thread; void* IntervalLastNg; void* IntervalLastOk; int /*<<< orphan*/  Hostname; int /*<<< orphan*/  Lock; int /*<<< orphan*/  HaltEvent; } ;
typedef  TYPE_1__ QUERYIPTHREAD ;

/* Variables and functions */
 int /*<<< orphan*/  NewEvent () ; 
 int /*<<< orphan*/  NewLock () ; 
 int /*<<< orphan*/  NewThread (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  QueryIpThreadMain ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,char*) ; 
 TYPE_1__* ZeroMalloc (int) ; 

QUERYIPTHREAD *NewQueryIpThread(char *hostname, UINT interval_last_ok, UINT interval_last_ng)
{
	QUERYIPTHREAD *t;

	t = ZeroMalloc(sizeof(QUERYIPTHREAD));

	t->HaltEvent = NewEvent();
	t->Lock = NewLock();
	StrCpy(t->Hostname, sizeof(t->Hostname), hostname);
	t->IntervalLastOk = interval_last_ok;
	t->IntervalLastNg = interval_last_ng;

	t->Thread = NewThread(QueryIpThreadMain, t);

	return t;
}