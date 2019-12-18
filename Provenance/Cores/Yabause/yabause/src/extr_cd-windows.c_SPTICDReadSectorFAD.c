#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_2__ {int enable_read_ahead; scalar_t__ FAD; int error_flag; scalar_t__ num_sectors_read; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SwitchToThread () ; 
 TYPE_1__ cd_buf ; 
 int /*<<< orphan*/  cd_cs ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,int) ; 

int SPTICDReadSectorFAD(u32 FAD, void *buffer) {
	// This function is supposed to read exactly 1 -RAW- 2352-byte sector at
	// the specified FAD address to buffer. Should return true if successful,
	// false if there was an error.
	//
	// Special Note: To convert from FAD to LBA/LSN, minus 150.
	//
	// The whole process needed to be changed since I need more control over
	// sector detection, etc. Not to mention it means less work for the porter
	// since they only have to implement raw sector reading as opposed to
	// implementing mode 1, mode 2 form1/form2, -and- raw sector reading.
	
	for (;;)
	{
		EnterCriticalSection(&cd_cs);
		if ((volatile)cd_buf.enable_read_ahead == 0)
		{
			if (cd_buf.FAD == FAD)
			{
				int ret;
				memcpy(buffer, cd_buf.data, 2352);
				ret = cd_buf.error_flag;
				LeaveCriticalSection(&cd_cs);
				return ret;
			}
			else
			{
				cd_buf.FAD = FAD;
				cd_buf.num_sectors_read = 0;
				cd_buf.error_flag = 0;
				cd_buf.enable_read_ahead = 1;
			}
		}
		LeaveCriticalSection(&cd_cs);
		SwitchToThread();
	}
}