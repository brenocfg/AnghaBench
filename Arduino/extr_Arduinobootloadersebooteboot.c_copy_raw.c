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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int FLASH_SECTOR_SIZE ; 
 scalar_t__ SPIEraseSector (int) ; 
 scalar_t__ SPIRead (int,int /*<<< orphan*/ *,int const) ; 
 scalar_t__ SPIWrite (int,int /*<<< orphan*/ *,int const) ; 

int copy_raw(const uint32_t src_addr,
             const uint32_t dst_addr,
             const uint32_t size)
{
    // require regions to be aligned
    if (src_addr & 0xfff != 0 ||
        dst_addr & 0xfff != 0) {
        return 1;
    }

    const uint32_t buffer_size = FLASH_SECTOR_SIZE;
    uint8_t buffer[buffer_size];
    uint32_t left = ((size+buffer_size-1) & ~(buffer_size-1));
    uint32_t saddr = src_addr;
    uint32_t daddr = dst_addr;

    while (left) {
        if (SPIEraseSector(daddr/buffer_size)) {
            return 2;
        }
        if (SPIRead(saddr, buffer, buffer_size)) {
            return 3;
        }
        if (SPIWrite(daddr, buffer, buffer_size)) {
            return 4;
        }
        saddr += buffer_size;
        daddr += buffer_size;
        left  -= buffer_size;
    }

    return 0;
}