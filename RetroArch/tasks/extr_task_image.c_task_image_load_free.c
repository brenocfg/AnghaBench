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
struct TYPE_3__ {scalar_t__ state; } ;
typedef  TYPE_1__ retro_task_t ;
typedef  int /*<<< orphan*/  nbio_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  task_image_cleanup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void task_image_load_free(retro_task_t *task)
{
   nbio_handle_t       *nbio  = task ? (nbio_handle_t*)task->state : NULL;

   if (nbio)
   {
      task_image_cleanup(nbio);
      free(nbio);
   }
}