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
struct TYPE_3__ {int /*<<< orphan*/ * data_received; int /*<<< orphan*/ * data_to_send; } ;
typedef  TYPE_1__ spi_slave_task_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vQueueDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vRingbufferDelete (int /*<<< orphan*/ *) ; 

void deinit_slave_context(spi_slave_task_context_t *context)
{
    TEST_ASSERT( context->data_to_send != NULL );
    vQueueDelete( context->data_to_send );
    context->data_to_send = NULL;
    TEST_ASSERT( context->data_received != NULL );
    vRingbufferDelete( context->data_received );
    context->data_received = NULL;
}