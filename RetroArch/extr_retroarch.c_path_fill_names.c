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
struct TYPE_4__ {int /*<<< orphan*/  ips; int /*<<< orphan*/  bps; int /*<<< orphan*/  ups; int /*<<< orphan*/  savefile; } ;
struct TYPE_5__ {TYPE_1__ name; } ;
typedef  TYPE_2__ global_t ;

/* Variables and functions */
 int /*<<< orphan*/  bsv_movie_set_path (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fill_pathname_noext (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 TYPE_2__ g_extern ; 
 int /*<<< orphan*/  path_init_savefile_internal () ; 
 int /*<<< orphan*/  path_main_basename ; 
 scalar_t__ string_is_empty (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void path_fill_names(void)
{
   global_t   *global = &g_extern;

   path_init_savefile_internal();

   if (global)
      bsv_movie_set_path(global->name.savefile);

   if (string_is_empty(path_main_basename))
      return;

   if (global)
   {
      if (string_is_empty(global->name.ups))
         fill_pathname_noext(global->name.ups, path_main_basename,
               ".ups",
               sizeof(global->name.ups));

      if (string_is_empty(global->name.bps))
         fill_pathname_noext(global->name.bps, path_main_basename,
               ".bps",
               sizeof(global->name.bps));

      if (string_is_empty(global->name.ips))
         fill_pathname_noext(global->name.ips, path_main_basename,
               ".ips",
               sizeof(global->name.ips));
   }
}