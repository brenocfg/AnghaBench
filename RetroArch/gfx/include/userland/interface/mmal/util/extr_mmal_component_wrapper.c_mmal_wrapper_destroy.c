#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  name; } ;
struct TYPE_8__ {int /*<<< orphan*/  sema; } ;
struct TYPE_7__ {unsigned int input_num; unsigned int output_num; scalar_t__* output_queue; scalar_t__* output_pool; scalar_t__* input_pool; TYPE_5__* component; } ;
typedef  TYPE_1__ MMAL_WRAPPER_T ;
typedef  TYPE_2__ MMAL_WRAPPER_PRIVATE_T ;
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_TRACE (char*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MMAL_SUCCESS ; 
 int /*<<< orphan*/  mmal_component_destroy (TYPE_5__*) ; 
 int /*<<< orphan*/  mmal_pool_destroy (scalar_t__) ; 
 int /*<<< orphan*/  mmal_queue_destroy (scalar_t__) ; 
 int /*<<< orphan*/  vcos_free (TYPE_2__*) ; 
 int /*<<< orphan*/  vcos_semaphore_delete (int /*<<< orphan*/ *) ; 

MMAL_STATUS_T mmal_wrapper_destroy(MMAL_WRAPPER_T *wrapper)
{
   MMAL_WRAPPER_PRIVATE_T *private = (MMAL_WRAPPER_PRIVATE_T *)wrapper;
   unsigned int i;

   LOG_TRACE("%p, %s", wrapper, wrapper->component->name);

   /* Cleanup resources */
   mmal_component_destroy(wrapper->component);

   for (i = 0; i < wrapper->input_num; i++)
   {
      if (wrapper->input_pool[i])
         mmal_pool_destroy(wrapper->input_pool[i]);
   }

   for (i = 0; i < wrapper->output_num; i++)
   {
      if (wrapper->output_pool[i])
         mmal_pool_destroy(wrapper->output_pool[i]);
      if (wrapper->output_queue[i])
         mmal_queue_destroy(wrapper->output_queue[i]);
   }

   vcos_semaphore_delete(&private->sema);
   vcos_free(private);
   return MMAL_SUCCESS;
}