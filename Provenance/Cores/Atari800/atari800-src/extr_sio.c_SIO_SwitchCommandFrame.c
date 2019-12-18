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
 scalar_t__ CommandIndex ; 
 scalar_t__ DataIndex ; 
 int ExpectedBytes ; 
 int /*<<< orphan*/  Log_print (char*,scalar_t__) ; 
 scalar_t__ SIO_CommandFrame ; 
 scalar_t__ SIO_NoFrame ; 
 scalar_t__ SIO_ReadFrame ; 
 scalar_t__ SIO_StatusRead ; 
 scalar_t__ TransferStatus ; 

void SIO_SwitchCommandFrame(int onoff)
{
	if (onoff) {				/* Enabled */
		if (TransferStatus != SIO_NoFrame)
			Log_print("Unexpected command frame at state %x.", TransferStatus);
		CommandIndex = 0;
		DataIndex = 0;
		ExpectedBytes = 5;
		TransferStatus = SIO_CommandFrame;
	}
	else {
		if (TransferStatus != SIO_StatusRead && TransferStatus != SIO_NoFrame &&
			TransferStatus != SIO_ReadFrame) {
			if (!(TransferStatus == SIO_CommandFrame && CommandIndex == 0))
				Log_print("Command frame %02x unfinished.", TransferStatus);
			TransferStatus = SIO_NoFrame;
		}
		CommandIndex = 0;
	}
}