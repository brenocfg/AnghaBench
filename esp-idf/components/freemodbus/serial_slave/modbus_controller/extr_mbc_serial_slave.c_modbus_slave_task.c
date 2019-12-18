#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  mbs_event_group; } ;
typedef  TYPE_1__ mb_slave_options_t ;
struct TYPE_4__ {TYPE_1__ opts; } ;
typedef  int BaseType_t ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  EV_FRAME_SENT ; 
 int MB_EVENT_STACK_STARTED ; 
 int /*<<< orphan*/  MB_SLAVE_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eMBPoll () ; 
 TYPE_2__* mbs_interface_ptr ; 
 int /*<<< orphan*/  pdFALSE ; 
 int /*<<< orphan*/  portMAX_DELAY ; 
 int xEventGroupWaitBits (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xMBPortEventPost (int /*<<< orphan*/ ) ; 
 scalar_t__ xMBPortSerialTxPoll () ; 

__attribute__((used)) static void modbus_slave_task(void *pvParameters)
{
    // Modbus interface must be initialized before start 
    MB_SLAVE_ASSERT(mbs_interface_ptr != NULL);
    mb_slave_options_t* mbs_opts = &mbs_interface_ptr->opts;
    
    MB_SLAVE_ASSERT(mbs_opts != NULL);
    // Main Modbus stack processing cycle
    for (;;) {
        BaseType_t status = xEventGroupWaitBits(mbs_opts->mbs_event_group,
                                                (BaseType_t)(MB_EVENT_STACK_STARTED),
                                                pdFALSE, // do not clear bits
                                                pdFALSE,
                                                portMAX_DELAY);
        // Check if stack started then poll for data
        if (status & MB_EVENT_STACK_STARTED) {
            (void)eMBPoll(); // allow stack to process data
            // Send response buffer
            BOOL xSentState = xMBPortSerialTxPoll(); 
            if (xSentState) {
                (void)xMBPortEventPost( EV_FRAME_SENT );
            }
        }
    }
}