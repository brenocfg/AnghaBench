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
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  MMAL_LIST_T ;
typedef  TYPE_1__ MMAL_LIST_PRIVATE_T ;

/* Variables and functions */
 int /*<<< orphan*/  vcos_free (TYPE_1__*) ; 
 int /*<<< orphan*/  vcos_mutex_delete (int /*<<< orphan*/ *) ; 

void mmal_list_destroy(MMAL_LIST_T *list)
{
   MMAL_LIST_PRIVATE_T *private = (MMAL_LIST_PRIVATE_T*)list;

   vcos_mutex_delete(&private->lock);
   vcos_free(private);
}