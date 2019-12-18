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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  Result ;
typedef  int /*<<< orphan*/  Handle ;

/* Variables and functions */
 int /*<<< orphan*/  AM_CancelCIAInstall (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AM_FinishCiaInstall (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AM_StartCiaInstall (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int FILE_CHUNK_SIZE ; 
 int /*<<< orphan*/  FSFILE_GetSize (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  FSFILE_Read (int /*<<< orphan*/ ,scalar_t__*,scalar_t__,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  FSFILE_Write (int /*<<< orphan*/ ,scalar_t__*,scalar_t__,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MEDIATYPE_SD ; 
 scalar_t__ RD_ALREADY_EXISTS ; 
 scalar_t__ R_DESCRIPTION (int /*<<< orphan*/ ) ; 
 scalar_t__ R_FAILED (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int installCia(Handle ciaFile){
	Result failed;
	Handle outputHandle;
	u64 fileSize;
	u64 fileOffset = 0;
	u32 bytesRead;
	u32 bytesWritten;
	u8 transferBuffer[FILE_CHUNK_SIZE];

	failed = AM_StartCiaInstall(MEDIATYPE_SD, &outputHandle);
	if(R_FAILED(failed))
		return -1;

	failed = FSFILE_GetSize(ciaFile, &fileSize);
	if(R_FAILED(failed))
		return -1;

	while(fileOffset < fileSize){
		u64 bytesRemaining = fileSize - fileOffset;
		failed = FSFILE_Read(ciaFile, &bytesRead, fileOffset, transferBuffer, bytesRemaining < FILE_CHUNK_SIZE ? bytesRemaining : FILE_CHUNK_SIZE);
		if(R_FAILED(failed)){
			AM_CancelCIAInstall(outputHandle);
			return -1;
		}

		failed = FSFILE_Write(outputHandle, &bytesWritten, fileOffset, transferBuffer, bytesRead, 0);
		if(R_FAILED(failed)){
			AM_CancelCIAInstall(outputHandle);
			if(R_DESCRIPTION(failed) == RD_ALREADY_EXISTS)
				return 1;
			return -1;
		}

		if(bytesWritten != bytesRead){
			AM_CancelCIAInstall(outputHandle);
			return -1;
		}

		fileOffset += bytesWritten;
	}

	failed = AM_FinishCiaInstall(outputHandle);
	if(R_FAILED(failed))
		return -1;

	return 1;
}