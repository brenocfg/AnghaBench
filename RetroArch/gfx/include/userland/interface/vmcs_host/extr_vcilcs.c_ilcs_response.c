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
typedef  scalar_t__ uint32_t ;
struct TYPE_5__ {int /*<<< orphan*/  wait_mtx; TYPE_1__* wait; } ;
struct TYPE_4__ {scalar_t__ xid; int* rlen; int /*<<< orphan*/  event; scalar_t__ resp; } ;
typedef  TYPE_1__ ILCS_WAIT_T ;
typedef  TYPE_2__ ILCS_SERVICE_T ;

/* Variables and functions */
 int ILCS_MAX_WAITING ; 
 int /*<<< orphan*/  memcpy (scalar_t__,unsigned char const*,int) ; 
 int /*<<< orphan*/  vcos_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_event_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ilcs_response(ILCS_SERVICE_T *st, uint32_t xid, const unsigned char *msg, int len)
{
   ILCS_WAIT_T *wait = NULL;
   int i, copy = len;

   // atomically retrieve given ->wait entry
   vcos_mutex_lock(&st->wait_mtx);
   for (i=0; i<ILCS_MAX_WAITING; i++) {
      wait = &st->wait[i];
      if(wait->resp && wait->xid == xid)
         break;
   }
   vcos_mutex_unlock(&st->wait_mtx);

   if(i == ILCS_MAX_WAITING) {
      // something bad happened, someone has sent a response back
      // when the caller said they weren't expecting a response
      vcos_assert(0);
      return;
   }

   // check that we have enough space to copy into.
   // if we haven't the user can tell by the updated rlen value.
   if(len > *wait->rlen)
      copy = *wait->rlen;

   *wait->rlen = len;

   // extract command from fifo and place in response buffer.
   memcpy(wait->resp, msg, copy);

   vcos_event_signal(&wait->event);
}