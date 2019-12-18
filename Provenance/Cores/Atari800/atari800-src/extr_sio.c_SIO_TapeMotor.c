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
 int /*<<< orphan*/  CASSETTE_TapeMotor (int) ; 
 scalar_t__ SIO_CasReadWrite ; 
 scalar_t__ SIO_NoFrame ; 
 int SIO_last_drive ; 
 int SIO_last_op_time ; 
 scalar_t__ TransferStatus ; 

void SIO_TapeMotor(int onoff)
{
	CASSETTE_TapeMotor(onoff);
	if (onoff) {
		/* set frame to cassette frame, if not */
		/* in a transfer with an intelligent peripheral */
		if (TransferStatus == SIO_NoFrame || TransferStatus == SIO_CasReadWrite)
			TransferStatus = SIO_CasReadWrite;
		SIO_last_drive = 0x60;
		SIO_last_op_time = 0x10;
	}
	else {
		/* set frame to none */
		if (TransferStatus == SIO_CasReadWrite)
			TransferStatus = SIO_NoFrame;
		SIO_last_op_time = 0;
	}
}