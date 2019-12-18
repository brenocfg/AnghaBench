#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  PSP_FLUSH_ALL () ; 
 scalar_t__ PSP_UC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  YAB_THREAD_SCSP ; 
 int /*<<< orphan*/  YabThreadWake (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  YabThreadYield () ; 
 int /*<<< orphan*/  scsp_clock ; 
 scalar_t__ scsp_clock_target ; 

__attribute__((used)) static void ScspSyncThread(void)
{
   PSP_FLUSH_ALL();
   while (PSP_UC(scsp_clock) != scsp_clock_target)
   {
      YabThreadWake(YAB_THREAD_SCSP);
      YabThreadYield();
   }
}