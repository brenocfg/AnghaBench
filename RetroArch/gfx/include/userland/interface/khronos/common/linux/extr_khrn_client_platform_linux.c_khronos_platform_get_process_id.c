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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  CLIENT_THREAD_STATE_T ;

/* Variables and functions */
 int /*<<< orphan*/ * CLIENT_GET_THREAD_STATE () ; 
 int /*<<< orphan*/  rpc_get_client_id (int /*<<< orphan*/ *) ; 

uint64_t khronos_platform_get_process_id()
{
   CLIENT_THREAD_STATE_T *thread = CLIENT_GET_THREAD_STATE();

   return rpc_get_client_id(thread);
}