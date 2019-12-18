#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  data ;
struct TYPE_6__ {scalar_t__ merge_pos; int /*<<< orphan*/  merge_buffer; } ;
typedef  TYPE_1__ CLIENT_THREAD_STATE_T ;

/* Variables and functions */
 scalar_t__ CLIENT_MAKE_CURRENT_SIZE ; 
 scalar_t__ EGLINTMAKECURRENT_ID ; 
 int /*<<< orphan*/  RPC_CALL8 (int /*<<< orphan*/ ,TYPE_1__*,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  eglIntMakeCurrent_impl ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rpc_begin (TYPE_1__*) ; 
 int /*<<< orphan*/  rpc_end (TYPE_1__*) ; 
 int /*<<< orphan*/  vcos_assert (int) ; 
 int /*<<< orphan*/  vcos_log_trace (char*) ; 

void rpc_call8_makecurrent(CLIENT_THREAD_STATE_T *thread, uint32_t id, uint32_t p0,
   uint32_t p1, uint32_t p2, uint32_t p3, uint32_t p4, uint32_t p5, uint32_t p6, uint32_t p7)
{
   uint32_t data;
   if (thread->merge_pos == CLIENT_MAKE_CURRENT_SIZE && (memcpy(&data,thread->merge_buffer,sizeof(data)), data == EGLINTMAKECURRENT_ID))
   {
      rpc_begin(thread);
      vcos_log_trace("rpc_call8_makecurrent collapse onto previous makecurrent");

      thread->merge_pos = 0;

      RPC_CALL8(eglIntMakeCurrent_impl, thread, EGLINTMAKECURRENT_ID, p0, p1, p2, p3, p4, p5, p6, p7);
      vcos_assert(thread->merge_pos == CLIENT_MAKE_CURRENT_SIZE);

      rpc_end(thread);
   }
   else
   {
      RPC_CALL8(eglIntMakeCurrent_impl, thread, EGLINTMAKECURRENT_ID, p0, p1, p2, p3, p4, p5, p6, p7);
   }
}