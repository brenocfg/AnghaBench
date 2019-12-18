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
struct storage_dio_context {int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  blocked_queue_terminate (int /*<<< orphan*/ *) ; 
 struct storage_dio_context* g_dio_contexts ; 
 int g_dio_thread_count ; 

void storage_dio_terminate()
{
	struct storage_dio_context *pContext;
	struct storage_dio_context *pContextEnd;

	pContextEnd = g_dio_contexts + g_dio_thread_count;
	for (pContext=g_dio_contexts; pContext<pContextEnd; pContext++)
	{
		blocked_queue_terminate(&(pContext->queue));
	}
}