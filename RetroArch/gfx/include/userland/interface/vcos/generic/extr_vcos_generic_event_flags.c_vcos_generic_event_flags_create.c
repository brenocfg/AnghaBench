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
typedef  int /*<<< orphan*/  VCOS_STATUS_T ;
struct TYPE_4__ {scalar_t__ tail; scalar_t__ head; } ;
struct TYPE_5__ {TYPE_1__ waiters; scalar_t__ events; int /*<<< orphan*/  lock; } ;
typedef  TYPE_2__ VCOS_EVENT_FLAGS_T ;

/* Variables and functions */
 int /*<<< orphan*/  VCOS_SUCCESS ; 
 int /*<<< orphan*/  vcos_mutex_create (int /*<<< orphan*/ *,char const*) ; 

VCOS_STATUS_T vcos_generic_event_flags_create(VCOS_EVENT_FLAGS_T *flags, const char *name)
{
   VCOS_STATUS_T rc;
   if ((rc=vcos_mutex_create(&flags->lock, name)) != VCOS_SUCCESS)
   {
      return rc;
   }

   flags->events = 0;
   flags->waiters.head = flags->waiters.tail = 0;
   return rc;
}