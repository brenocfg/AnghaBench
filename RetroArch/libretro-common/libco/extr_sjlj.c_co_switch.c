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
typedef  scalar_t__ cothread_t ;
struct TYPE_3__ {int /*<<< orphan*/  context; } ;
typedef  TYPE_1__ cothread_struct ;

/* Variables and functions */
 TYPE_1__* co_running ; 
 int /*<<< orphan*/  siglongjmp (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sigsetjmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void co_switch(cothread_t cothread)
{
   if (!sigsetjmp(co_running->context, 0))
   {
      co_running = (cothread_struct*)cothread;
      siglongjmp(co_running->context, 1);
   }
}