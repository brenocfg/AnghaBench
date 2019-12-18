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
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ CARDIO_ERROR_READY ; 
 scalar_t__ sdgecko_writeSectors (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void const*) ; 

__attribute__((used)) static bool __gcsd_writeSectors(int n, u32 sector, u32 numSectors, const void *buffer)
{
	s32 ret;

	ret = sdgecko_writeSectors(n,sector,numSectors,buffer);
	if(ret == CARDIO_ERROR_READY)
		return true;

	return false;
}