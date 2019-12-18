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
struct TYPE_5__ {int /*<<< orphan*/  source_file; } ;
typedef  TYPE_2__ decompress_state_t ;

/* Variables and functions */
 int string_is_equal (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ task_decompress_handler ; 

__attribute__((used)) static bool task_decompress_finder(
      retro_task_t *task, void *user_data)
{
   decompress_state_t *dec = (decompress_state_t*)task->state;

   if (task->handler != task_decompress_handler)
      return false;

   return string_is_equal(dec->source_file, (const char*)user_data);
}