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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  sec_t ;
typedef  int /*<<< orphan*/  CACHE ;

/* Variables and functions */
 int /*<<< orphan*/  _FAT_cache_readPartialSector (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int,int) ; 
 int /*<<< orphan*/  u8array_to_u16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u8array_to_u32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

bool _FAT_cache_readLittleEndianValue (CACHE* cache, uint32_t *value, sec_t sector, unsigned int offset, int num_bytes) {
  uint8_t buf[4];
  if (!_FAT_cache_readPartialSector(cache, buf, sector, offset, num_bytes)) return false;

  switch(num_bytes) {
  case 1: *value = buf[0]; break;
  case 2: *value = u8array_to_u16(buf,0); break;
  case 4: *value = u8array_to_u32(buf,0); break;
  default: return false;
  }
  return true;
}