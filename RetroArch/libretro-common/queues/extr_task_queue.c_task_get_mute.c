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
struct TYPE_3__ {int mute; } ;
typedef  TYPE_1__ retro_task_t ;

/* Variables and functions */
 int /*<<< orphan*/  SLOCK_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SLOCK_UNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  property_lock ; 

bool task_get_mute(retro_task_t *task)
{
   bool mute = false;

   SLOCK_LOCK(property_lock);
   mute = task->mute;
   SLOCK_UNLOCK(property_lock);

   return mute;
}