#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  sema; int /*<<< orphan*/  event; scalar_t__ comp; } ;
typedef  scalar_t__ OMX_ERRORTYPE ;
typedef  TYPE_1__ COMPONENT_T ;

/* Variables and functions */
 scalar_t__ OMX_ErrorNone ; 
 scalar_t__ OMX_FreeHandle (scalar_t__) ; 
 int /*<<< orphan*/  ilclient_return_events (TYPE_1__*) ; 
 int /*<<< orphan*/  vc_assert (int) ; 
 int /*<<< orphan*/  vcos_event_flags_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_free (TYPE_1__*) ; 
 int /*<<< orphan*/  vcos_semaphore_delete (int /*<<< orphan*/ *) ; 

void ilclient_cleanup_components(COMPONENT_T *list[])
{
   int i;
   OMX_ERRORTYPE error;

   i=0;
   while (list[i])
   {
      ilclient_return_events(list[i]);
      if (list[i]->comp)
      {
         error = OMX_FreeHandle(list[i]->comp);

         vc_assert(error == OMX_ErrorNone);
      }
      i++;
   }

   i=0;
   while (list[i])
   {
      vcos_event_flags_delete(&list[i]->event);
      vcos_semaphore_delete(&list[i]->sema);
      vcos_free(list[i]);
      list[i] = NULL;
      i++;
   }
}