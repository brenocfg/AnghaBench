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
struct TYPE_2__ {int /*<<< orphan*/  (* Reset ) () ;} ;

/* Variables and functions */
 TYPE_1__* M68K ; 
 int /*<<< orphan*/  PSP_FLUSH_ALL () ; 
 int /*<<< orphan*/  ScspSyncThread () ; 
 int m68k_running ; 
 scalar_t__ m68k_saved_cycles ; 
 scalar_t__ scsp_thread_running ; 
 int /*<<< orphan*/  stub1 () ; 

void M68KStart(void)
{
   if (scsp_thread_running)
      ScspSyncThread();

   M68K->Reset();
   m68k_saved_cycles = 0;

   m68k_running = 1;

   if (scsp_thread_running)
      PSP_FLUSH_ALL();
}