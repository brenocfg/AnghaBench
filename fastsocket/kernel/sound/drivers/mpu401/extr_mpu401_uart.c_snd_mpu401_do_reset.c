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
struct snd_mpu401 {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  MPU401_ENTER_UART ; 
 int /*<<< orphan*/  MPU401_RESET ; 
 scalar_t__ snd_mpu401_uart_cmd (struct snd_mpu401*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int snd_mpu401_do_reset(struct snd_mpu401 *mpu)
{
	if (snd_mpu401_uart_cmd(mpu, MPU401_RESET, 1))
		return -EIO;
	if (snd_mpu401_uart_cmd(mpu, MPU401_ENTER_UART, 0))
		return -EIO;
	return 0;
}