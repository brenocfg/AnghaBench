#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_4__ {scalar_t__ merge_pos; scalar_t__ merge_end; } ;
typedef  TYPE_1__ CLIENT_THREAD_STATE_T ;

/* Variables and functions */
 scalar_t__ MERGE_BUFFER_SIZE ; 
 int /*<<< orphan*/  merge_flush (TYPE_1__*) ; 
 scalar_t__ rpc_pad_ctrl (scalar_t__) ; 
 int /*<<< orphan*/  vcos_assert (int) ; 

void rpc_send_ctrl_begin(CLIENT_THREAD_STATE_T *thread, uint32_t len)
{
   //CLIENT_THREAD_STATE_T *thread = CLIENT_GET_THREAD_STATE();

   vcos_assert(len == rpc_pad_ctrl(len));
   if ((thread->merge_pos + len) > MERGE_BUFFER_SIZE) {
      merge_flush(thread);
   }

   thread->merge_end = thread->merge_pos + len;
}