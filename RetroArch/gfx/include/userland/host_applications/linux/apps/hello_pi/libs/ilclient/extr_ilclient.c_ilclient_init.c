#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* event_rep; TYPE_1__* event_list; int /*<<< orphan*/  event_sema; } ;
struct TYPE_8__ {int eEvent; struct TYPE_8__* next; } ;
typedef  TYPE_2__ ILCLIENT_T ;

/* Variables and functions */
 int NUM_EVENTS ; 
 int /*<<< orphan*/  VCOS_LOG_CATEGORY ; 
 int /*<<< orphan*/  VCOS_LOG_WARN ; 
 int VCOS_SUCCESS ; 
 int /*<<< orphan*/  ilclient_lock_events (TYPE_2__*) ; 
 int /*<<< orphan*/  ilclient_unlock_events (TYPE_2__*) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vc_assert (int) ; 
 int /*<<< orphan*/  vcos_log_register (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_log_set_level (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* vcos_malloc (int,char*) ; 
 int vcos_semaphore_create (int /*<<< orphan*/ *,char*,int) ; 

ILCLIENT_T *ilclient_init()
{
   ILCLIENT_T *st = vcos_malloc(sizeof(ILCLIENT_T), "ilclient");
   int i;

   if (!st)
      return NULL;

   vcos_log_set_level(VCOS_LOG_CATEGORY, VCOS_LOG_WARN);
   vcos_log_register("ilclient", VCOS_LOG_CATEGORY);

   memset(st, 0, sizeof(ILCLIENT_T));

   i = vcos_semaphore_create(&st->event_sema, "il:event", 1);
   vc_assert(i == VCOS_SUCCESS);

   ilclient_lock_events(st);
   st->event_list = NULL;
   for (i=0; i<NUM_EVENTS; i++)
   {
      st->event_rep[i].eEvent = -1; // mark as unused
      st->event_rep[i].next = st->event_list;
      st->event_list = st->event_rep+i;
   }
   ilclient_unlock_events(st);
   return st;
}