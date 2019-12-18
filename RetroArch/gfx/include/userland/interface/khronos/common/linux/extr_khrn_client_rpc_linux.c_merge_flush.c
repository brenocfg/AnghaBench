#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ VCHIQ_STATUS_T ;
struct TYPE_9__ {scalar_t__ size; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ VCHIQ_ELEMENT_T ;
struct TYPE_10__ {scalar_t__ merge_pos; int /*<<< orphan*/  merge_buffer; } ;
typedef  TYPE_2__ CLIENT_THREAD_STATE_T ;

/* Variables and functions */
 scalar_t__ CLIENT_MAKE_CURRENT_SIZE ; 
 int /*<<< orphan*/  UNUSED_NDEBUG (scalar_t__) ; 
 scalar_t__ VCHIQ_SUCCESS ; 
 int /*<<< orphan*/  client_send_make_current (TYPE_2__*) ; 
 int /*<<< orphan*/  get_handle (TYPE_2__*) ; 
 int /*<<< orphan*/  rpc_begin (TYPE_2__*) ; 
 int /*<<< orphan*/  rpc_end (TYPE_2__*) ; 
 scalar_t__ vchiq_queue_message (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  vcos_assert (int) ; 
 int /*<<< orphan*/  vcos_log_trace (char*) ; 

__attribute__((used)) static void merge_flush(CLIENT_THREAD_STATE_T *thread)
{
   vcos_log_trace("merge_flush start");

   vcos_assert(thread->merge_pos >= CLIENT_MAKE_CURRENT_SIZE);

   /*
      don't transmit just a make current -- in the case that there is only a
      make current in the merge buffer, we have already sent a control message
      for the rpc call (and with it a make current) and own the big lock
   */

   if (thread->merge_pos > CLIENT_MAKE_CURRENT_SIZE) {
      VCHIQ_ELEMENT_T element;

      rpc_begin(thread);

      element.data = thread->merge_buffer;
      element.size = thread->merge_pos;

      VCHIQ_STATUS_T success = vchiq_queue_message(get_handle(thread), &element, 1);
      UNUSED_NDEBUG(success);
      vcos_assert(success == VCHIQ_SUCCESS);

      thread->merge_pos = 0;

      client_send_make_current(thread);

      vcos_assert(thread->merge_pos == CLIENT_MAKE_CURRENT_SIZE);

      rpc_end(thread);
   }
   vcos_log_trace( "merge_flush end");

}