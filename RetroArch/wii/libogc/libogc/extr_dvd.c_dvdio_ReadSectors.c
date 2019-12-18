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
typedef  int sec_t ;
typedef  int /*<<< orphan*/  dvdcmdblk ;

/* Variables and functions */
 scalar_t__ DVD_ReadPrio (int /*<<< orphan*/ *,void*,int,int,int) ; 

__attribute__((used)) static bool dvdio_ReadSectors(sec_t sector,sec_t numSectors,void *buffer)
{
	dvdcmdblk blk;

	if(DVD_ReadPrio(&blk, buffer, numSectors<<11, sector << 11, 2) <= 0)
		return false;

	return true;
}