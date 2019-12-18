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
struct oxygen {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPU401_ENTER_UART ; 
 int /*<<< orphan*/  MPU401_RESET ; 
 int /*<<< orphan*/  _write_uart (struct oxygen*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 

void oxygen_reset_uart(struct oxygen *chip)
{
	_write_uart(chip, 1, MPU401_RESET);
	msleep(1); /* wait for ACK */
	_write_uart(chip, 1, MPU401_ENTER_UART);
}