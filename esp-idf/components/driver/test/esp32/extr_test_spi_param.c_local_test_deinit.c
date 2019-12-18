#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  slave_context; scalar_t__ handle_slave; } ;
typedef  TYPE_1__ spitest_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  deinit_slave_context (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vTaskDelete (scalar_t__) ; 

__attribute__((used)) static void local_test_deinit(void* arg)
{
    spitest_context_t* context = arg;
    vTaskDelete(context->handle_slave);
    context->handle_slave = 0;
    deinit_slave_context(&context->slave_context);
}