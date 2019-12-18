#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  target_val; scalar_t__ target_kaddr; int /*<<< orphan*/  lock; int /*<<< orphan*/  started_event; } ;
typedef  TYPE_1__ mch2_thread_args_t ;

/* Variables and functions */
 int /*<<< orphan*/  U64_MAX ; 
 int /*<<< orphan*/  svcExitThread () ; 
 int /*<<< orphan*/  svcSignalEvent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svcWaitSynchronization (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_kaddr (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void target_thread_entry(mch2_thread_args_t* args)
{
   svcSignalEvent(args->started_event);
   svcWaitSynchronization(args->lock, U64_MAX);

   if (args->target_kaddr)
      write_kaddr(args->target_kaddr, args->target_val);

   svcExitThread();
}