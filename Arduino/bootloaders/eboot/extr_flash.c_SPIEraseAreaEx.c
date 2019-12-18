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
typedef  int uint32_t ;

/* Variables and functions */
 int FLASH_BLOCK_SIZE ; 
 int FLASH_SECTOR_SIZE ; 
 scalar_t__ SPIEraseBlock (int) ; 
 scalar_t__ SPIEraseSector (int) ; 

int SPIEraseAreaEx(const uint32_t start, const uint32_t size)
{
    if (start & (FLASH_SECTOR_SIZE - 1) != 0) {
        return 1;
    }

    const uint32_t sectors_per_block = FLASH_BLOCK_SIZE / FLASH_SECTOR_SIZE;
    uint32_t current_sector = start / FLASH_SECTOR_SIZE;
    uint32_t sector_count = (size + FLASH_SECTOR_SIZE - 1) / FLASH_SECTOR_SIZE;
    const uint32_t end = current_sector + sector_count;

    for (; current_sector < end && (current_sector & (sectors_per_block-1)); 
        ++current_sector, --sector_count) {
        if (SPIEraseSector(current_sector)) {
            return 2;
        }
    }

    for (;current_sector + sectors_per_block <= end; 
        current_sector += sectors_per_block, 
        sector_count -= sectors_per_block) {
        if (SPIEraseBlock(current_sector / sectors_per_block)) {
            return 3;
        }
    }

    for (; current_sector < end; 
        ++current_sector, --sector_count) {
        if (SPIEraseSector(current_sector)) {
            return 4;
        }
    }

    return 0;
}