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
struct netfs_inode_info {void* ino; void* version; void* size; void* rdev; void* blocks; void* blocksize; void* gid; void* uid; void* nlink; void* mode; } ;

/* Variables and functions */
 void* __cpu_to_be32 (void*) ; 
 void* __cpu_to_be64 (void*) ; 

__attribute__((used)) static inline void netfs_convert_inode_info(struct netfs_inode_info *info)
{
	info->mode = __cpu_to_be32(info->mode);
	info->nlink = __cpu_to_be32(info->nlink);
	info->uid = __cpu_to_be32(info->uid);
	info->gid = __cpu_to_be32(info->gid);
	info->blocksize = __cpu_to_be32(info->blocksize);
	info->blocks = __cpu_to_be64(info->blocks);
	info->rdev = __cpu_to_be64(info->rdev);
	info->size = __cpu_to_be64(info->size);
	info->version = __cpu_to_be64(info->version);
	info->ino = __cpu_to_be64(info->ino);
}