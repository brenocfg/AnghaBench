#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ length; int /*<<< orphan*/ * last; int /*<<< orphan*/ * first; } ;
struct TYPE_7__ {TYPE_1__ list; int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ MMAL_LIST_T ;
typedef  TYPE_2__ MMAL_LIST_PRIVATE_T ;

/* Variables and functions */
 scalar_t__ VCOS_SUCCESS ; 
 int /*<<< orphan*/  vcos_free (TYPE_2__*) ; 
 TYPE_2__* vcos_malloc (int,char*) ; 
 scalar_t__ vcos_mutex_create (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  vcos_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_mutex_unlock (int /*<<< orphan*/ *) ; 

MMAL_LIST_T* mmal_list_create(void)
{
   MMAL_LIST_PRIVATE_T *private;

   private = vcos_malloc(sizeof(MMAL_LIST_PRIVATE_T), "mmal-list");
   if (private == NULL)
      goto error;

   if (vcos_mutex_create(&private->lock, "mmal-list lock") != VCOS_SUCCESS)
      goto error;

   /* lock to keep coverity happy */
   vcos_mutex_lock(&private->lock);
   private->list.first = NULL;
   private->list.last = NULL;
   private->list.length = 0;
   vcos_mutex_unlock(&private->lock);

   return &private->list;

error:
   vcos_free(private);
   return NULL;
}