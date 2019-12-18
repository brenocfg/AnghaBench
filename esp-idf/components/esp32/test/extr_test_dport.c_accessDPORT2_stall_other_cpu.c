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

/* Variables and functions */
 int /*<<< orphan*/  DPORT_DATE_REG ; 
 int /*<<< orphan*/  DPORT_STALL_OTHER_CPU_END () ; 
 int /*<<< orphan*/  DPORT_STALL_OTHER_CPU_START () ; 
 int /*<<< orphan*/  XTHAL_GET_CCOUNT () ; 
 int /*<<< orphan*/  XTHAL_SET_CCOMPARE (int,int /*<<< orphan*/ ) ; 
 scalar_t__ _DPORT_REG_READ (int /*<<< orphan*/ ) ; 
 int apb_test_result ; 
 int dport_test_result ; 
 int exit_flag ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  vTaskDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xSemaphoreGive (int /*<<< orphan*/ ) ; 
 int xt_highint5_read_apb ; 

__attribute__((used)) static void accessDPORT2_stall_other_cpu(void *pvParameters)
{
    xSemaphoreHandle *sema = (xSemaphoreHandle *) pvParameters;
    dport_test_result = true;
    while (exit_flag == false) {
        DPORT_STALL_OTHER_CPU_START();
        XTHAL_SET_CCOMPARE(2, XTHAL_GET_CCOUNT());
        xt_highint5_read_apb = 1;
        for (int i = 0; i < 200; ++i) {
            if (_DPORT_REG_READ(DPORT_DATE_REG) != _DPORT_REG_READ(DPORT_DATE_REG)) {
                apb_test_result = false;
                break;
            }
        }
        xt_highint5_read_apb = 0;
        DPORT_STALL_OTHER_CPU_END();
    }
    printf("accessDPORT2_stall_other_cpu finish\n");

    xSemaphoreGive(*sema);
    vTaskDelete(NULL);
}