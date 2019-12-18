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
struct TYPE_3__ {int /*<<< orphan*/  mbm_event_group; } ;
typedef  TYPE_1__ mb_master_options_t ;
struct TYPE_4__ {TYPE_1__ opts; } ;
typedef  int BaseType_t ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  EV_MASTER_FRAME_TRANSMITTED ; 
 int MB_EVENT_STACK_STARTED ; 
 int /*<<< orphan*/  MB_MASTER_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eMBMasterPoll () ; 
 TYPE_2__* mbm_interface_ptr ; 
 int /*<<< orphan*/  pdFALSE ; 
 int /*<<< orphan*/  portMAX_DELAY ; 
 int xEventGroupWaitBits (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xMBMasterPortEventPost (int /*<<< orphan*/ ) ; 
 scalar_t__ xMBMasterPortSerialTxPoll () ; 

__attribute__((used)) static void modbus_master_task(void *pvParameters)
{
    // The interface must be initialized before start of state machine
    MB_MASTER_ASSERT(mbm_interface_ptr != NULL);
    mb_master_options_t* mbm_opts = &mbm_interface_ptr->opts;
    // Main Modbus stack processing cycle
    for (;;) {
        // Wait for poll events
        BaseType_t status = xEventGroupWaitBits(mbm_opts->mbm_event_group,
                                                (BaseType_t)(MB_EVENT_STACK_STARTED),
                                                pdFALSE, // do not clear bits
                                                pdFALSE,
                                                portMAX_DELAY);
        // Check if stack started then poll for data
        if (status & MB_EVENT_STACK_STARTED) {
            (void)eMBMasterPoll(); // Allow stack to process data
            // Send response buffer if ready to be sent
            BOOL xSentState = xMBMasterPortSerialTxPoll();
            if (xSentState) {
                // Let state machine know that response was transmitted out
                (void)xMBMasterPortEventPost(EV_MASTER_FRAME_TRANSMITTED);
            }
        }
    }
}