#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct stat {int st_mode; int st_nlink; int st_uid; int st_gid; int st_size; int st_blksize; int st_blocks; scalar_t__* st_spare4; scalar_t__ st_spare3; void* st_ctime; scalar_t__ st_spare2; void* st_mtime; scalar_t__ st_spare1; void* st_atime; int /*<<< orphan*/  st_dev; int /*<<< orphan*/  st_rdev; scalar_t__ st_ino; } ;
typedef  scalar_t__ ino_t ;
struct TYPE_9__ {int /*<<< orphan*/  entryData; } ;
struct TYPE_8__ {int bytesPerSector; int /*<<< orphan*/  disc; } ;
typedef  TYPE_1__ PARTITION ;
typedef  TYPE_2__ DIR_ENTRY ;

/* Variables and functions */
 int /*<<< orphan*/  DIR_ENTRY_aDate ; 
 int /*<<< orphan*/  DIR_ENTRY_cDate ; 
 int /*<<< orphan*/  DIR_ENTRY_cTime ; 
 int /*<<< orphan*/  DIR_ENTRY_fileSize ; 
 int /*<<< orphan*/  DIR_ENTRY_mDate ; 
 int /*<<< orphan*/  DIR_ENTRY_mTime ; 
 int S_IFDIR ; 
 int S_IFREG ; 
 int S_IRGRP ; 
 int S_IROTH ; 
 int S_IRUSR ; 
 int S_IWGRP ; 
 int S_IWOTH ; 
 int S_IWUSR ; 
 scalar_t__ _FAT_directory_entryGetCluster (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ _FAT_directory_isDirectory (TYPE_2__*) ; 
 scalar_t__ _FAT_directory_isWritable (TYPE_2__*) ; 
 int /*<<< orphan*/  _FAT_disc_hostType (int /*<<< orphan*/ ) ; 
 void* _FAT_filetime_to_time_t (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u8array_to_u16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int u8array_to_u32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void _FAT_directory_entryStat (PARTITION* partition, DIR_ENTRY* entry, struct stat *st) {
	// Fill in the stat struct
	// Some of the values are faked for the sake of compatibility
	st->st_dev = _FAT_disc_hostType(partition->disc);					// The device is the 32bit ioType value
  	st->st_ino = (ino_t)(_FAT_directory_entryGetCluster(partition, entry->entryData));		// The file serial number is the start cluster
	st->st_mode = (_FAT_directory_isDirectory(entry) ? S_IFDIR : S_IFREG) |
		(S_IRUSR | S_IRGRP | S_IROTH) |
		(_FAT_directory_isWritable (entry) ? (S_IWUSR | S_IWGRP | S_IWOTH) : 0);		// Mode bits based on dirEntry ATTRIB byte
	st->st_nlink = 1;								// Always one hard link on a FAT file
	st->st_uid = 1;									// Faked for FAT
	st->st_gid = 2;									// Faked for FAT
	st->st_rdev = st->st_dev;
	st->st_size = u8array_to_u32 (entry->entryData, DIR_ENTRY_fileSize);		// File size
	st->st_atime = _FAT_filetime_to_time_t (
		0,
		u8array_to_u16 (entry->entryData, DIR_ENTRY_aDate)
	);
	st->st_spare1 = 0;
	st->st_mtime = _FAT_filetime_to_time_t (
		u8array_to_u16 (entry->entryData, DIR_ENTRY_mTime),
		u8array_to_u16 (entry->entryData, DIR_ENTRY_mDate)
	);
	st->st_spare2 = 0;
	st->st_ctime = _FAT_filetime_to_time_t (
		u8array_to_u16 (entry->entryData, DIR_ENTRY_cTime),
		u8array_to_u16 (entry->entryData, DIR_ENTRY_cDate)
	);
	st->st_spare3 = 0;
	st->st_blksize = partition->bytesPerSector;				// Prefered file I/O block size
	st->st_blocks = (st->st_size + partition->bytesPerSector - 1) / partition->bytesPerSector;	// File size in blocks
	st->st_spare4[0] = 0;
	st->st_spare4[1] = 0;
}