#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char file_type; int /*<<< orphan*/  formatted_ext_name; int /*<<< orphan*/  mtime; int /*<<< orphan*/  crc32; int /*<<< orphan*/  file_size; int /*<<< orphan*/  alloc_size; } ;
typedef  TYPE_1__ FDFSTrunkHeader ;

/* Variables and functions */
 scalar_t__ FDFS_FILE_EXT_NAME_MAX_LEN ; 
 int FDFS_TRUNK_FILE_ALLOC_SIZE_OFFSET ; 
 int FDFS_TRUNK_FILE_FILE_CRC32_OFFSET ; 
 int FDFS_TRUNK_FILE_FILE_EXT_NAME_OFFSET ; 
 int FDFS_TRUNK_FILE_FILE_MTIME_OFFSET ; 
 int FDFS_TRUNK_FILE_FILE_SIZE_OFFSET ; 
 int FDFS_TRUNK_FILE_FILE_TYPE_OFFSET ; 
 int /*<<< orphan*/  int2buff (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,scalar_t__) ; 

void trunk_pack_header(const FDFSTrunkHeader *pTrunkHeader, char *buff)
{
	*(buff + FDFS_TRUNK_FILE_FILE_TYPE_OFFSET) = pTrunkHeader->file_type;
	int2buff(pTrunkHeader->alloc_size, \
		buff + FDFS_TRUNK_FILE_ALLOC_SIZE_OFFSET);
	int2buff(pTrunkHeader->file_size, \
		buff + FDFS_TRUNK_FILE_FILE_SIZE_OFFSET);
	int2buff(pTrunkHeader->crc32, \
		buff + FDFS_TRUNK_FILE_FILE_CRC32_OFFSET);
	int2buff(pTrunkHeader->mtime, \
		buff + FDFS_TRUNK_FILE_FILE_MTIME_OFFSET);
	memcpy(buff + FDFS_TRUNK_FILE_FILE_EXT_NAME_OFFSET, \
		pTrunkHeader->formatted_ext_name, \
		FDFS_FILE_EXT_NAME_MAX_LEN + 1);
}