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
struct TYPE_3__ {int pos_increment; int /*<<< orphan*/  handle; scalar_t__ is_finished; } ;
typedef  TYPE_1__ nbio_handle_t ;

/* Variables and functions */
 scalar_t__ nbio_iterate (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int task_file_transfer_iterate_transfer(nbio_handle_t *nbio)
{
   size_t i;

   nbio->pos_increment = 5;

   if (nbio->is_finished)
      return 0;

   for (i = 0; i < nbio->pos_increment; i++)
   {
      if (nbio_iterate(nbio->handle))
         return -1;
   }

   return 0;
}