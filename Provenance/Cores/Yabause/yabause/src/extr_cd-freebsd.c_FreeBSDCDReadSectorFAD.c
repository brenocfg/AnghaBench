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
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int hCDROM ; 
 int /*<<< orphan*/  lseek (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read (int,void*,int) ; 

__attribute__((used)) static int FreeBSDCDReadSectorFAD(u32 FAD, void *buffer) {
	if (hCDROM != -1)
	{
		lseek(hCDROM, (FAD - 150) * 2352, SEEK_SET);
		read(hCDROM, buffer, 2352);
	
		return 1;
	}

	return 0;
}