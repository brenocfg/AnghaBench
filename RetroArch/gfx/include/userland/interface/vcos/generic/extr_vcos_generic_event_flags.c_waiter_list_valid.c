#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* head; TYPE_2__* tail; } ;
struct TYPE_7__ {TYPE_1__ waiters; } ;
typedef  TYPE_3__ VCOS_EVENT_FLAGS_T ;
struct TYPE_6__ {int /*<<< orphan*/ * next; } ;

/* Variables and functions */

__attribute__((used)) static int waiter_list_valid(VCOS_EVENT_FLAGS_T *flags)
{
   int valid;
   /* Either both head and tail are NULL, or neither are NULL */
   if (flags->waiters.head == NULL)
   {
      valid = (flags->waiters.tail == NULL);
   }
   else
   {
      valid = (flags->waiters.tail != NULL);
   }

   /* If head and tail point at the same non-NULL element, then there
    * is only one element in the list.
    */
   if (flags->waiters.head && (flags->waiters.head == flags->waiters.tail))
   {
      valid = (flags->waiters.head->next == NULL);
   }
   return valid;
}