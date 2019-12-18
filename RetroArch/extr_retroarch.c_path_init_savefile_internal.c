#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  savefile; } ;
struct TYPE_5__ {TYPE_1__ name; } ;
typedef  TYPE_2__ global_t ;

/* Variables and functions */
 TYPE_2__ g_extern ; 
 int /*<<< orphan*/  path_deinit_savefile () ; 
 int /*<<< orphan*/  path_init_savefile_new () ; 
 int /*<<< orphan*/  path_init_savefile_rtc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  path_init_subsystem () ; 

__attribute__((used)) static void path_init_savefile_internal(void)
{
   path_deinit_savefile();

   path_init_savefile_new();

   if (!path_init_subsystem())
   {
      global_t   *global = &g_extern;
      path_init_savefile_rtc(global->name.savefile);
   }
}