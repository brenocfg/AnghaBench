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
struct TYPE_3__ {void* userdata; int /*<<< orphan*/  func; } ;
typedef  TYPE_1__ task_finder_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  task_decompress_finder ; 
 int task_queue_find (TYPE_1__*) ; 

bool task_check_decompress(const char *source_file)
{
   task_finder_data_t find_data;

   /* Prepare find parameters */
   find_data.func     = task_decompress_finder;
   find_data.userdata = (void *)source_file;

   /* Return whether decompressing is in progress or not */
   return task_queue_find(&find_data);
}