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
 int /*<<< orphan*/  FDCREG_STATUS ; 
 unsigned char FDC_READ (int /*<<< orphan*/ ) ; 
 scalar_t__ FD_MOTOR_OFF_MAXTRY ; 
 int HZ ; 
 int /*<<< orphan*/  MotorOffTrys ; 
 scalar_t__ MotorOn ; 
 scalar_t__ SelectedDrive ; 
 int /*<<< orphan*/  fd_deselect () ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  motor_off_timer ; 
 scalar_t__ stdma_islocked () ; 

__attribute__((used)) static void fd_motor_off_timer( unsigned long dummy )
{
	unsigned char status;

	if (SelectedDrive < 0)
		/* no drive selected, needn't deselect anyone */
		return;

	if (stdma_islocked())
		goto retry;

	status = FDC_READ( FDCREG_STATUS );

	if (!(status & 0x80)) {
		/* motor already turned off by FDC -> deselect drives */
		MotorOn = 0;
		fd_deselect();
		return;
	}
	/* not yet off, try again */

  retry:
	/* Test again later; if tested too often, it seems there is no disk
	 * in the drive and the FDC will leave the motor on forever (or,
	 * at least until a disk is inserted). So we'll test only twice
	 * per second from then on...
	 */
	mod_timer(&motor_off_timer,
		  jiffies + (MotorOffTrys++ < FD_MOTOR_OFF_MAXTRY ? HZ/20 : HZ/2));
}