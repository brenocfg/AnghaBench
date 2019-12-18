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
typedef  char UBYTE ;

/* Variables and functions */
 int /*<<< orphan*/  BINLOAD_start_binloading ; 
 int /*<<< orphan*/  CASSETTE_PutByte (int) ; 
 int* CommandFrame ; 
 int CommandIndex ; 
 char* DataBuffer ; 
 int DataIndex ; 
 int ExpectedBytes ; 
 int /*<<< orphan*/  Log_print (char*) ; 
 scalar_t__ POKEY_DELAYED_SERIN_IRQ ; 
 scalar_t__ SIO_ACK_INTERVAL ; 
#define  SIO_CasReadWrite 130 
 char SIO_ChkSum (char*,int /*<<< orphan*/ ) ; 
#define  SIO_CommandFrame 129 
 int SIO_FinalStatus ; 
 int SIO_NoFrame ; 
 int /*<<< orphan*/  SIO_OFF ; 
 scalar_t__ SIO_SERIN_INTERVAL ; 
 int SIO_StatusRead ; 
#define  SIO_WriteFrame 128 
 int /*<<< orphan*/ * SIO_drive_status ; 
 int TransferStatus ; 
 char WriteSectorBack () ; 

void SIO_PutByte(int byte)
{
	switch (TransferStatus) {
	case SIO_CommandFrame:
		if (CommandIndex < ExpectedBytes) {
			CommandFrame[CommandIndex++] = byte;
			if (CommandIndex >= ExpectedBytes) {
				if (CommandFrame[0] >= 0x31 && CommandFrame[0] <= 0x38 && (SIO_drive_status[CommandFrame[0]-0x31] != SIO_OFF || BINLOAD_start_binloading)) {
					TransferStatus = SIO_StatusRead;
					POKEY_DELAYED_SERIN_IRQ = SIO_SERIN_INTERVAL + SIO_ACK_INTERVAL;
				}
				else
					TransferStatus = SIO_NoFrame;
			}
		}
		else {
			Log_print("Invalid command frame!");
			TransferStatus = SIO_NoFrame;
		}
		break;
	case SIO_WriteFrame:		/* Expect data */
		if (DataIndex < ExpectedBytes) {
			DataBuffer[DataIndex++] = byte;
			if (DataIndex >= ExpectedBytes) {
				UBYTE sum = SIO_ChkSum(DataBuffer, ExpectedBytes - 1);
				if (sum == DataBuffer[ExpectedBytes - 1]) {
					UBYTE result = WriteSectorBack();
					if (result != 0) {
						DataBuffer[0] = 'A';
						DataBuffer[1] = result;
						DataIndex = 0;
						ExpectedBytes = 2;
						POKEY_DELAYED_SERIN_IRQ = SIO_SERIN_INTERVAL + SIO_ACK_INTERVAL;
						TransferStatus = SIO_FinalStatus;
					}
					else
						TransferStatus = SIO_NoFrame;
				}
				else {
					DataBuffer[0] = 'E';
					DataIndex = 0;
					ExpectedBytes = 1;
					POKEY_DELAYED_SERIN_IRQ = SIO_SERIN_INTERVAL + SIO_ACK_INTERVAL;
					TransferStatus = SIO_FinalStatus;
				}
			}
		}
		else {
			Log_print("Invalid data frame!");
		}
		break;
	case SIO_CasReadWrite:
		CASSETTE_PutByte(byte);
		break;
	}
	/* POKEY_DELAYED_SEROUT_IRQ = SIO_SEROUT_INTERVAL; */ /* already set in pokey.c */
}