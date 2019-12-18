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
typedef  int /*<<< orphan*/  xSemaphoreHandle ;
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  DPORT_DATE_REG ; 
 scalar_t__ DPORT_REG_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPORT_STALL_OTHER_CPU_END () ; 
 int /*<<< orphan*/  DPORT_STALL_OTHER_CPU_START () ; 
 scalar_t__ _DPORT_REG_READ (int /*<<< orphan*/ ) ; 
 int apb_test_result ; 
 int dport_test_result ; 
 int exit_flag ; 
 scalar_t__ stall_other_cpu_counter ; 
 int /*<<< orphan*/  vTaskDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xSemaphoreGive (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void accessDPORT_stall_other_cpu(void *pvParameters)
{
    xSemaphoreHandle *sema = (xSemaphoreHandle *) pvParameters;
    uint32_t dport_date = DPORT_REG_READ(DPORT_DATE_REG);
    uint32_t dport_date_cur;
    dport_test_result = true;
    stall_other_cpu_counter = 0;
    // although exit flag is set in another task, checking (exit_flag == false) is safe
    while (exit_flag == false) {
        ++stall_other_cpu_counter;
        DPORT_STALL_OTHER_CPU_START();
        dport_date_cur = _DPORT_REG_READ(DPORT_DATE_REG);
        DPORT_STALL_OTHER_CPU_END();
        if (dport_date != dport_date_cur) {
            apb_test_result = false;
            break;
        }
    }

    xSemaphoreGive(*sema);
    vTaskDelete(NULL);
}