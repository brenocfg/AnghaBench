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
 int /*<<< orphan*/  D (int /*<<< orphan*/ ) ; 
 int* DataBuffer ; 
 int DataIndex ; 
 int ExpectedBytes ; 
 int /*<<< orphan*/  Log_print (char*) ; 
 int PIO_Command_Frame () ; 
#define  PIO_FinalStatus 131 
#define  PIO_FormatFrame 130 
 int PIO_NoFrame ; 
#define  PIO_ReadFrame 129 
#define  PIO_StatusRead 128 
 int TransferStatus ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 

__attribute__((used)) static int PIO_GetByte(void)
{
	int byte = 0;
	D(printf("PIO_GetByte TransferStatus:%d\n",TransferStatus));

	switch (TransferStatus) {
	case PIO_StatusRead:
		byte = PIO_Command_Frame();		/* Handle now the command */
		break;
	case PIO_FormatFrame:
		TransferStatus = PIO_ReadFrame;
		/*DELAYED_SERIN_IRQ = SERIN_INTERVAL << 3;*/
		/* FALL THROUGH */
	case PIO_ReadFrame:
		D(printf("ReadFrame: DataIndex:%d ExpectedBytes:%d\n",DataIndex,ExpectedBytes));
		if (DataIndex < ExpectedBytes) {
			byte = DataBuffer[DataIndex++];
			if (DataIndex >= ExpectedBytes) {
				TransferStatus = PIO_NoFrame;
			}
			/*else {*/
				/* set delay using the expected transfer speed */
				/*DELAYED_SERIN_IRQ = (DataIndex == 1) ? SERIN_INTERVAL*/
					/*: ((SERIN_INTERVAL * AUDF[CHAN3] - 1) / 0x28 + 1);*/
			/*}*/
		}
		else {
			Log_print("Invalid read frame!");
			TransferStatus = PIO_NoFrame;
		}
		break;
	case PIO_FinalStatus:
		if (DataIndex < ExpectedBytes) {
			byte = DataBuffer[DataIndex++];
			if (DataIndex >= ExpectedBytes) {
				TransferStatus = PIO_NoFrame;
			}
			/*else {
				if (DataIndex == 0)
					DELAYED_SERIN_IRQ = SERIN_INTERVAL + ACK_INTERVAL;
				else
					DELAYED_SERIN_IRQ = SERIN_INTERVAL;
			}*/
		}
		else {
			Log_print("Invalid read frame!");
			TransferStatus = PIO_NoFrame;
		}
		break;
	default:
		break;
	}
	return byte;
}