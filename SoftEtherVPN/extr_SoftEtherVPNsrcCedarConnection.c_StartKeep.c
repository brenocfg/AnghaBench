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
struct TYPE_5__ {int /*<<< orphan*/  Thread; int /*<<< orphan*/  Cancel; int /*<<< orphan*/  HaltEvent; int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ KEEP ;

/* Variables and functions */
 int /*<<< orphan*/  KeepThread ; 
 int /*<<< orphan*/  NewCancel () ; 
 int /*<<< orphan*/  NewEvent () ; 
 int /*<<< orphan*/  NewLock () ; 
 int /*<<< orphan*/  NewThread (int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_1__* ZeroMalloc (int) ; 

KEEP *StartKeep()
{
	KEEP *k = ZeroMalloc(sizeof(KEEP));

	k->lock = NewLock();
	k->HaltEvent = NewEvent();
	k->Cancel = NewCancel();

	// Thread start
	k->Thread = NewThread(KeepThread, k);

	return k;
}