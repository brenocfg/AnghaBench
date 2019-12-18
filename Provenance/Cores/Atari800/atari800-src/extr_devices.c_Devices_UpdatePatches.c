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
 scalar_t__ B_DEVICE_BEGIN ; 
 scalar_t__ B_DEVICE_END ; 
 scalar_t__ B_PATCH_CLOS ; 
 scalar_t__ B_PATCH_INIT ; 
 scalar_t__ B_PATCH_OPEN ; 
 scalar_t__ B_PATCH_READ ; 
 scalar_t__ B_PATCH_SPEC ; 
 scalar_t__ B_PATCH_STAT ; 
 scalar_t__ B_PATCH_WRIT ; 
 scalar_t__ B_TABLE_ADDRESS ; 
 int /*<<< orphan*/  Devices_B_Close ; 
 int /*<<< orphan*/  Devices_B_Init ; 
 int /*<<< orphan*/  Devices_B_Null ; 
 int /*<<< orphan*/  Devices_B_Open ; 
 int /*<<< orphan*/  Devices_B_Read ; 
 int /*<<< orphan*/  Devices_B_Write ; 
 int /*<<< orphan*/  Devices_H_Close ; 
 int /*<<< orphan*/  Devices_H_Open ; 
 int /*<<< orphan*/  Devices_H_Read ; 
 int /*<<< orphan*/  Devices_H_Special ; 
 int /*<<< orphan*/  Devices_H_Status ; 
 int /*<<< orphan*/  Devices_H_Write ; 
 int /*<<< orphan*/  Devices_RemoveHATABSEntry (char,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ Devices_TABLE_CLOS ; 
 scalar_t__ Devices_TABLE_INIT ; 
 scalar_t__ Devices_TABLE_OPEN ; 
 scalar_t__ Devices_TABLE_READ ; 
 scalar_t__ Devices_TABLE_SPEC ; 
 scalar_t__ Devices_TABLE_STAT ; 
 scalar_t__ Devices_TABLE_WRIT ; 
 scalar_t__ Devices_enable_b_patch ; 
 scalar_t__ Devices_enable_h_patch ; 
 scalar_t__ Devices_enable_r_patch ; 
 int /*<<< orphan*/  ESC_AddEscRts (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESC_BCLOS ; 
 int /*<<< orphan*/  ESC_BINIT ; 
 int /*<<< orphan*/  ESC_BOPEN ; 
 int /*<<< orphan*/  ESC_BREAD ; 
 int /*<<< orphan*/  ESC_BSPEC ; 
 int /*<<< orphan*/  ESC_BSTAT ; 
 int /*<<< orphan*/  ESC_BWRIT ; 
 int /*<<< orphan*/  ESC_HHCLOS ; 
 int /*<<< orphan*/  ESC_HHOPEN ; 
 int /*<<< orphan*/  ESC_HHREAD ; 
 int /*<<< orphan*/  ESC_HHSPEC ; 
 int /*<<< orphan*/  ESC_HHSTAT ; 
 int /*<<< orphan*/  ESC_HHWRIT ; 
 int /*<<< orphan*/  ESC_RCLOS ; 
 int /*<<< orphan*/  ESC_RINIT ; 
 int /*<<< orphan*/  ESC_ROPEN ; 
 int /*<<< orphan*/  ESC_RREAD ; 
 int /*<<< orphan*/  ESC_RSPEC ; 
 int /*<<< orphan*/  ESC_RSTAT ; 
 int /*<<< orphan*/  ESC_RWRIT ; 
 int /*<<< orphan*/  ESC_Remove (int /*<<< orphan*/ ) ; 
 scalar_t__ H_DEVICE_BEGIN ; 
 scalar_t__ H_DEVICE_END ; 
 scalar_t__ H_PATCH_CLOS ; 
 scalar_t__ H_PATCH_OPEN ; 
 scalar_t__ H_PATCH_READ ; 
 scalar_t__ H_PATCH_SPEC ; 
 scalar_t__ H_PATCH_STAT ; 
 scalar_t__ H_PATCH_WRIT ; 
 scalar_t__ H_TABLE_ADDRESS ; 
 int /*<<< orphan*/  MEMORY_SetROM (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  MEMORY_dFillMem (scalar_t__,int,scalar_t__) ; 
 int /*<<< orphan*/  MEMORY_dPutWord (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  RDevice_CLOS ; 
 int /*<<< orphan*/  RDevice_INIT ; 
 int /*<<< orphan*/  RDevice_OPEN ; 
 int /*<<< orphan*/  RDevice_READ ; 
 int /*<<< orphan*/  RDevice_SPEC ; 
 int /*<<< orphan*/  RDevice_STAT ; 
 int /*<<< orphan*/  RDevice_WRIT ; 
 scalar_t__ R_DEVICE_BEGIN ; 
 scalar_t__ R_DEVICE_END ; 
 scalar_t__ R_PATCH_CLOS ; 
 scalar_t__ R_PATCH_INIT ; 
 scalar_t__ R_PATCH_OPEN ; 
 scalar_t__ R_PATCH_READ ; 
 scalar_t__ R_PATCH_SPEC ; 
 scalar_t__ R_PATCH_STAT ; 
 scalar_t__ R_PATCH_WRIT ; 
 scalar_t__ R_TABLE_ADDRESS ; 
 int /*<<< orphan*/  b_entry_address ; 
 int /*<<< orphan*/  h_entry_address ; 
 int /*<<< orphan*/  r_entry_address ; 

void Devices_UpdatePatches(void)
{
	if (Devices_enable_h_patch) {		/* enable H: device */
		/* change memory attributes for the area, where we put
		   the H: handler table and patches */
		MEMORY_SetROM(H_DEVICE_BEGIN, H_DEVICE_END);
		/* set handler table */
		MEMORY_dPutWord(H_TABLE_ADDRESS + Devices_TABLE_OPEN, H_PATCH_OPEN - 1);
		MEMORY_dPutWord(H_TABLE_ADDRESS + Devices_TABLE_CLOS, H_PATCH_CLOS - 1);
		MEMORY_dPutWord(H_TABLE_ADDRESS + Devices_TABLE_READ, H_PATCH_READ - 1);
		MEMORY_dPutWord(H_TABLE_ADDRESS + Devices_TABLE_WRIT, H_PATCH_WRIT - 1);
		MEMORY_dPutWord(H_TABLE_ADDRESS + Devices_TABLE_STAT, H_PATCH_STAT - 1);
		MEMORY_dPutWord(H_TABLE_ADDRESS + Devices_TABLE_SPEC, H_PATCH_SPEC - 1);
		/* set patches */
		ESC_AddEscRts(H_PATCH_OPEN, ESC_HHOPEN, Devices_H_Open);
		ESC_AddEscRts(H_PATCH_CLOS, ESC_HHCLOS, Devices_H_Close);
		ESC_AddEscRts(H_PATCH_READ, ESC_HHREAD, Devices_H_Read);
		ESC_AddEscRts(H_PATCH_WRIT, ESC_HHWRIT, Devices_H_Write);
		ESC_AddEscRts(H_PATCH_STAT, ESC_HHSTAT, Devices_H_Status);
		ESC_AddEscRts(H_PATCH_SPEC, ESC_HHSPEC, Devices_H_Special);
		/* H: in HATABS will be added next frame by Devices_Frame */
	}
	else {						/* disable H: device */
		/* remove H: entry from HATABS */
		Devices_RemoveHATABSEntry('H', h_entry_address, H_TABLE_ADDRESS);
		/* remove patches */
		ESC_Remove(ESC_HHOPEN);
		ESC_Remove(ESC_HHCLOS);
		ESC_Remove(ESC_HHREAD);
		ESC_Remove(ESC_HHWRIT);
		ESC_Remove(ESC_HHSTAT);
		ESC_Remove(ESC_HHSPEC);
		/* fill memory area used for table and patches with 0xff */
		MEMORY_dFillMem(H_DEVICE_BEGIN, 0xff, H_DEVICE_END - H_DEVICE_BEGIN + 1);
	}

#ifdef R_IO_DEVICE
	if (Devices_enable_r_patch) {		/* enable R: device */
		/* change memory attributes for the area, where we put
		   the R: handler table and patches */
		MEMORY_SetROM(R_DEVICE_BEGIN, R_DEVICE_END);
		/* set handler table */
		MEMORY_dPutWord(R_TABLE_ADDRESS + Devices_TABLE_OPEN, R_PATCH_OPEN - 1);
		MEMORY_dPutWord(R_TABLE_ADDRESS + Devices_TABLE_CLOS, R_PATCH_CLOS - 1);
		MEMORY_dPutWord(R_TABLE_ADDRESS + Devices_TABLE_READ, R_PATCH_READ - 1);
		MEMORY_dPutWord(R_TABLE_ADDRESS + Devices_TABLE_WRIT, R_PATCH_WRIT - 1);
		MEMORY_dPutWord(R_TABLE_ADDRESS + Devices_TABLE_STAT, R_PATCH_STAT - 1);
		MEMORY_dPutWord(R_TABLE_ADDRESS + Devices_TABLE_SPEC, R_PATCH_SPEC - 1);
		MEMORY_dPutWord(R_TABLE_ADDRESS + Devices_TABLE_INIT, R_PATCH_INIT - 1);
		/* set patches */
		ESC_AddEscRts(R_PATCH_OPEN, ESC_ROPEN, RDevice_OPEN);
		ESC_AddEscRts(R_PATCH_CLOS, ESC_RCLOS, RDevice_CLOS);
		ESC_AddEscRts(R_PATCH_READ, ESC_RREAD, RDevice_READ);
		ESC_AddEscRts(R_PATCH_WRIT, ESC_RWRIT, RDevice_WRIT);
		ESC_AddEscRts(R_PATCH_STAT, ESC_RSTAT, RDevice_STAT);
		ESC_AddEscRts(R_PATCH_SPEC, ESC_RSPEC, RDevice_SPEC);
		ESC_AddEscRts(R_PATCH_INIT, ESC_RINIT, RDevice_INIT);
		/* R: in HATABS will be added next frame by Devices_Frame */
	}
	else {						/* disable R: device */
		/* remove R: entry from HATABS */
		Devices_RemoveHATABSEntry('R', r_entry_address, R_TABLE_ADDRESS);
		/* remove patches */
		ESC_Remove(ESC_ROPEN);
		ESC_Remove(ESC_RCLOS);
		ESC_Remove(ESC_RREAD);
		ESC_Remove(ESC_RWRIT);
		ESC_Remove(ESC_RSTAT);
		ESC_Remove(ESC_RSPEC);
		/* fill memory area used for table and patches with 0xff */
		MEMORY_dFillMem(R_DEVICE_BEGIN, 0xff, R_DEVICE_END - R_DEVICE_BEGIN + 1);
	}
#endif /* defined(R_IO_DEVICE) */

	if (Devices_enable_b_patch) {
		/* add B: device to HATABS */
		MEMORY_SetROM(B_DEVICE_BEGIN, B_DEVICE_END);
		/* set handler table */
		MEMORY_dPutWord(B_TABLE_ADDRESS + Devices_TABLE_OPEN, B_PATCH_OPEN - 1);
		MEMORY_dPutWord(B_TABLE_ADDRESS + Devices_TABLE_CLOS, B_PATCH_CLOS - 1);
		MEMORY_dPutWord(B_TABLE_ADDRESS + Devices_TABLE_READ, B_PATCH_READ - 1);
		MEMORY_dPutWord(B_TABLE_ADDRESS + Devices_TABLE_WRIT, B_PATCH_WRIT - 1);
		MEMORY_dPutWord(B_TABLE_ADDRESS + Devices_TABLE_STAT, B_PATCH_STAT - 1);
		MEMORY_dPutWord(B_TABLE_ADDRESS + Devices_TABLE_SPEC, B_PATCH_SPEC - 1);
		MEMORY_dPutWord(B_TABLE_ADDRESS + Devices_TABLE_INIT, B_PATCH_INIT - 1);
		/* set patches */
		ESC_AddEscRts(B_PATCH_OPEN, ESC_BOPEN, Devices_B_Open);
		ESC_AddEscRts(B_PATCH_CLOS, ESC_BCLOS, Devices_B_Close);
		ESC_AddEscRts(B_PATCH_READ, ESC_BREAD, Devices_B_Read);
		ESC_AddEscRts(B_PATCH_WRIT, ESC_BWRIT, Devices_B_Write);
		ESC_AddEscRts(B_PATCH_STAT, ESC_BSTAT, Devices_B_Null);
		ESC_AddEscRts(B_PATCH_SPEC, ESC_BSPEC, Devices_B_Null);
		ESC_AddEscRts(B_PATCH_INIT, ESC_BINIT, Devices_B_Init);
	}
	else {
		/* remove B: entry from HATABS */
		Devices_RemoveHATABSEntry('B', b_entry_address, B_TABLE_ADDRESS);
		/* remove patches */
		ESC_Remove(ESC_BOPEN);
		ESC_Remove(ESC_BCLOS);
		ESC_Remove(ESC_BREAD);
		ESC_Remove(ESC_BWRIT);
		ESC_Remove(ESC_BSTAT);
		ESC_Remove(ESC_BSPEC);
		/* fill memory area used for table and patches with 0xff */
		MEMORY_dFillMem(B_DEVICE_BEGIN, 0xff, B_DEVICE_END - B_DEVICE_BEGIN + 1);
	}
}