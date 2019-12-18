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
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_5__ {int /*<<< orphan*/  Thread; void* FlushEvent; void* Event; int /*<<< orphan*/  RecordQueue; int /*<<< orphan*/  SwitchType; void* Prefix; void* DirName; int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ LOG ;

/* Variables and functions */
 void* CopyStr (char*) ; 
 int /*<<< orphan*/  LogThread ; 
 void* NewEvent () ; 
 int /*<<< orphan*/  NewLock () ; 
 int /*<<< orphan*/  NewQueue () ; 
 int /*<<< orphan*/  NewThread (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  WaitThreadInit (int /*<<< orphan*/ ) ; 
 TYPE_1__* ZeroMalloc (int) ; 

LOG *NewLog(char *dir, char *prefix, UINT switch_type)
{
	LOG *g;

	g = ZeroMalloc(sizeof(LOG));
	g->lock = NewLock();
	g->DirName = CopyStr(dir == NULL ? "" : dir);
	g->Prefix = CopyStr(prefix == NULL ? "log" : prefix);
	g->SwitchType = switch_type;
	g->RecordQueue = NewQueue();
	g->Event = NewEvent();
	g->FlushEvent = NewEvent();

	g->Thread = NewThread(LogThread, g);

	WaitThreadInit(g->Thread);

	return g;
}