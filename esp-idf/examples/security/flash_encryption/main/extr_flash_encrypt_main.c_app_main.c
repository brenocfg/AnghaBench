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
 int /*<<< orphan*/  example_print_chip_info () ; 
 int /*<<< orphan*/  example_print_flash_encryption_status () ; 
 int /*<<< orphan*/  example_read_write_flash () ; 
 int /*<<< orphan*/  printf (char*) ; 

void app_main(void)
{
    printf("\nExample to check Flash Encryption status\n");

    example_print_chip_info();
    example_print_flash_encryption_status();
    example_read_write_flash();
}