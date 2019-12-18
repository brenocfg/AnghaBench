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
 void* BINLOAD_start_binloading ; 
 int /*<<< orphan*/  Devices_H_BinLoaderCont () ; 
 int /*<<< orphan*/  Devices_ICAX1Z ; 
 int /*<<< orphan*/  Devices_ICAX2Z ; 
 void* FALSE ; 
 int MEMORY_dGetByte (int /*<<< orphan*/ ) ; 
 void* TRUE ; 
 void* initBinFile ; 
 void* runBinFile ; 

__attribute__((used)) static void Devices_H_LoadProceed(int mydos)
{
	/* Log_print("MyDOS %d, AX1 %d, AX2 %d", mydos, MEMORY_dGetByte(Devices_ICAX1Z), MEMORY_dGetByte(Devices_ICAX2Z)); */
	if (mydos) {
		switch (MEMORY_dGetByte(Devices_ICAX1Z) /* XXX: & 7 ? */) {
		case 4:
			runBinFile = TRUE;
			initBinFile = TRUE;
			break;
		case 5:
			runBinFile = TRUE;
			initBinFile = FALSE;
			break;
		case 6:
			runBinFile = FALSE;
			initBinFile = TRUE;
			break;
		case 7:
		default:
			runBinFile = FALSE;
			initBinFile = FALSE;
			break;
		}
	}
	else {
		if (MEMORY_dGetByte(Devices_ICAX2Z) < 128)
			runBinFile = TRUE;
		else
			runBinFile = FALSE;
		initBinFile = TRUE;
	}

	BINLOAD_start_binloading = TRUE;
	Devices_H_BinLoaderCont();
}