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
typedef  int /*<<< orphan*/  PARTITION ;
typedef  int /*<<< orphan*/  DISC_INTERFACE ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_SECTOR_SIZE ; 
 scalar_t__ _FAT_mem_align (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _FAT_mem_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * _FAT_partition_constructor_buf (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

PARTITION* _FAT_partition_constructor (const DISC_INTERFACE* disc, uint32_t cacheSize, uint32_t sectorsPerPage, sec_t startSector)
{
   PARTITION *ret        = NULL;
	uint8_t *sectorBuffer = (uint8_t*) _FAT_mem_align(MAX_SECTOR_SIZE);
	if (!sectorBuffer)
      return NULL;

	ret = _FAT_partition_constructor_buf(disc, cacheSize,
			sectorsPerPage, startSector, sectorBuffer);
	_FAT_mem_free(sectorBuffer);
	return ret;
}