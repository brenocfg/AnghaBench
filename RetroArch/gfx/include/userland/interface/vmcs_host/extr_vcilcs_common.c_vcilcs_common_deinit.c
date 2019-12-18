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
struct TYPE_5__ {struct TYPE_5__* next; struct TYPE_5__* component_list; int /*<<< orphan*/  component_lock; } ;
typedef  TYPE_1__ VC_PRIVATE_COMPONENT_T ;
typedef  TYPE_1__ ILCS_COMMON_T ;

/* Variables and functions */
 int /*<<< orphan*/  vcos_free (TYPE_1__*) ; 
 int /*<<< orphan*/  vcos_semaphore_delete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vcilcs_common_deinit(ILCS_COMMON_T *st)
{
   vcos_semaphore_delete(&st->component_lock);

   while(st->component_list)
   {
      VC_PRIVATE_COMPONENT_T *comp = st->component_list;
      st->component_list = comp->next;
      vcos_free(comp);
   }

   vcos_free(st);
}