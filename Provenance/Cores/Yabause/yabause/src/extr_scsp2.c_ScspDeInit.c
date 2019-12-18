#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  (* DeInit ) () ;} ;

/* Variables and functions */
 TYPE_1__* SNDCore ; 
 int /*<<< orphan*/ * SoundRam ; 
 int /*<<< orphan*/  T2MemoryDeInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  YAB_THREAD_SCSP ; 
 int /*<<< orphan*/  YabThreadWait (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  YabThreadWake (int /*<<< orphan*/ ) ; 
 scalar_t__ scsp_thread_running ; 
 int /*<<< orphan*/  stub1 () ; 

void ScspDeInit(void)
{
   if (scsp_thread_running)
   {
      scsp_thread_running = 0;  // Tell the subthread to stop
      YabThreadWake(YAB_THREAD_SCSP);
      YabThreadWait(YAB_THREAD_SCSP);
   }

   if (SNDCore)
      SNDCore->DeInit();
   SNDCore = NULL;

   if (SoundRam)
      T2MemoryDeInit(SoundRam);
   SoundRam = NULL;
}