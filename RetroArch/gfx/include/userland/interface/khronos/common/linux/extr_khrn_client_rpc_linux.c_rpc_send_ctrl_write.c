#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {scalar_t__ merge_buffer; scalar_t__ merge_pos; } ;
typedef  TYPE_1__ CLIENT_THREAD_STATE_T ;

/* Variables and functions */
 scalar_t__ MERGE_BUFFER_SIZE ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 scalar_t__ rpc_pad_ctrl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_assert (int) ; 

void rpc_send_ctrl_write(CLIENT_THREAD_STATE_T *thread, const uint32_t in[], uint32_t len) /* len bytes read, rpc_pad_ctrl(len) bytes written */
{
   //CLIENT_THREAD_STATE_T *thread = CLIENT_GET_THREAD_STATE();

   memcpy(thread->merge_buffer + thread->merge_pos, in, len);
   thread->merge_pos += rpc_pad_ctrl(len);
   vcos_assert(thread->merge_pos <= MERGE_BUFFER_SIZE);
}