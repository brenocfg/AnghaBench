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
struct TYPE_3__ {scalar_t__ merge_pos; scalar_t__ merge_end; } ;
typedef  TYPE_1__ CLIENT_THREAD_STATE_T ;

/* Variables and functions */
 int /*<<< orphan*/  vcos_assert (int) ; 

void rpc_send_ctrl_end(CLIENT_THREAD_STATE_T *thread)
{
   //CLIENT_THREAD_STATE_T *thread = CLIENT_GET_THREAD_STATE();

   vcos_assert(thread->merge_pos == thread->merge_end);
}