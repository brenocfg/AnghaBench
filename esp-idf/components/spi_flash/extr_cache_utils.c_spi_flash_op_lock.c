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
 int /*<<< orphan*/  portMAX_DELAY ; 
 int /*<<< orphan*/  s_flash_op_mutex ; 
 int /*<<< orphan*/  xSemaphoreTakeRecursive (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void spi_flash_op_lock(void)
{
    xSemaphoreTakeRecursive(s_flash_op_mutex, portMAX_DELAY);
}