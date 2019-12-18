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
 int CASSETTE_GetByte () ; 
 int Command_Frame () ; 
 int* DataBuffer ; 
 int DataIndex ; 
 int ExpectedBytes ; 
 int /*<<< orphan*/  Log_print (char*) ; 
 int* POKEY_AUDF ; 
 size_t POKEY_CHAN3 ; 
 int POKEY_DELAYED_SERIN_IRQ ; 
 int SIO_ACK_INTERVAL ; 
#define  SIO_CasReadWrite 132 
#define  SIO_FinalStatus 131 
#define  SIO_FormatFrame 130 
 int SIO_NoFrame ; 
#define  SIO_ReadFrame 129 
 int SIO_SERIN_INTERVAL ; 
#define  SIO_StatusRead 128 
 int TransferStatus ; 

int SIO_GetByte(void)
{
	int byte = 0;

	switch (TransferStatus) {
	case SIO_StatusRead:
		byte = Command_Frame();		/* Handle now the command */
		break;
	case SIO_FormatFrame:
		TransferStatus = SIO_ReadFrame;
		POKEY_DELAYED_SERIN_IRQ = SIO_SERIN_INTERVAL << 3;
		/* FALL THROUGH */
	case SIO_ReadFrame:
		if (DataIndex < ExpectedBytes) {
			byte = DataBuffer[DataIndex++];
			if (DataIndex >= ExpectedBytes) {
				TransferStatus = SIO_NoFrame;
			}
			else {
				/* set delay using the expected transfer speed */
				POKEY_DELAYED_SERIN_IRQ = (DataIndex == 1) ? SIO_SERIN_INTERVAL
					: ((SIO_SERIN_INTERVAL * POKEY_AUDF[POKEY_CHAN3] - 1) / 0x28 + 1);
			}
		}
		else {
			Log_print("Invalid read frame!");
			TransferStatus = SIO_NoFrame;
		}
		break;
	case SIO_FinalStatus:
		if (DataIndex < ExpectedBytes) {
			byte = DataBuffer[DataIndex++];
			if (DataIndex >= ExpectedBytes) {
				TransferStatus = SIO_NoFrame;
			}
			else {
				if (DataIndex == 0)
					POKEY_DELAYED_SERIN_IRQ = SIO_SERIN_INTERVAL + SIO_ACK_INTERVAL;
				else
					POKEY_DELAYED_SERIN_IRQ = SIO_SERIN_INTERVAL;
			}
		}
		else {
			Log_print("Invalid read frame!");
			TransferStatus = SIO_NoFrame;
		}
		break;
	case SIO_CasReadWrite:
		byte = CASSETTE_GetByte();
		break;
	default:
		break;
	}
	return byte;
}