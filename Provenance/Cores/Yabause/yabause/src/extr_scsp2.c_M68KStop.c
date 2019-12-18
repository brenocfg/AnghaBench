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
 int /*<<< orphan*/  ScspSyncThread () ; 
 scalar_t__ m68k_running ; 
 scalar_t__ scsp_thread_running ; 

void M68KStop(void)
{
   if (scsp_thread_running)
      ScspSyncThread();

   m68k_running = 0;

   if (scsp_thread_running)
      PSP_FLUSH_ALL();
}