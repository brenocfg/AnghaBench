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
struct TYPE_4__ {scalar_t__ handler; scalar_t__ state; } ;
typedef  TYPE_1__ retro_task_t ;
struct TYPE_5__ {int /*<<< orphan*/  overlay_path; } ;
typedef  TYPE_2__ overlay_loader_t ;

/* Variables and functions */
 int string_is_equal (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ task_overlay_handler ; 

__attribute__((used)) static bool task_overlay_finder(retro_task_t *task, void *user_data)
{
   overlay_loader_t *loader = NULL;

   if (!task || (task->handler != task_overlay_handler))
      return false;

   if (!user_data)
      return false;

   loader = (overlay_loader_t*)task->state;
   if (!loader)
      return false;

   return string_is_equal(loader->overlay_path, (const char*)user_data);
}