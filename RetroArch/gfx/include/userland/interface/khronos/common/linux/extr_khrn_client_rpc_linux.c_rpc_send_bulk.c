#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  CLIENT_THREAD_STATE_T ;

/* Variables and functions */
 int /*<<< orphan*/  merge_flush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  send_bulk (int /*<<< orphan*/ *,void const*,scalar_t__) ; 

void rpc_send_bulk(CLIENT_THREAD_STATE_T *thread, const void *in, uint32_t len)
{
   if (in && len) {
      //CLIENT_THREAD_STATE_T *thread = CLIENT_GET_THREAD_STATE();

      merge_flush(thread);

      send_bulk(thread, in, len);
   }
}