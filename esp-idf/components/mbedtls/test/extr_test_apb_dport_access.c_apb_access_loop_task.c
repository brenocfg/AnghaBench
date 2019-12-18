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

/* Variables and functions */
 scalar_t__ REG_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UART_DATE_REG (int /*<<< orphan*/ ) ; 
 int apb_access_corrupt ; 

__attribute__((used)) static void apb_access_loop_task(void *ignore)
{
    uint32_t initial = REG_READ(UART_DATE_REG(0));
    while(1) {
        if (REG_READ(UART_DATE_REG(0)) != initial) {
            apb_access_corrupt = true;
        }
    }
}