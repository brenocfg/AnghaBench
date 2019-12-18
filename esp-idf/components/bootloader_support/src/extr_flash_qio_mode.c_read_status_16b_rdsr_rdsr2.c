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

/* Variables and functions */
 int /*<<< orphan*/  CMD_RDSR ; 
 int /*<<< orphan*/  CMD_RDSR2 ; 
 int execute_flash_command (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static unsigned read_status_16b_rdsr_rdsr2(void)
{
    return execute_flash_command(CMD_RDSR, 0, 0, 8) | (execute_flash_command(CMD_RDSR2, 0, 0, 8) << 8);
}