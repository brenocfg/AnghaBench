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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int IOSUHAX_FSA_RawRead (int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IOSUHAX_sdio_isInserted () ; 
 int /*<<< orphan*/  fsaFdSd ; 
 int /*<<< orphan*/  sdioFd ; 

__attribute__((used)) static bool IOSUHAX_sdio_readSectors(uint32_t sector, uint32_t numSectors, void* buffer)
{
    if(!IOSUHAX_sdio_isInserted() || !buffer)
        return false;

    int res = IOSUHAX_FSA_RawRead(fsaFdSd, buffer, 512, numSectors, sector, sdioFd);
    if(res < 0)
    {
        return false;
    }

    return true;
}