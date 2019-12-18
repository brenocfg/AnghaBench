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

/* Variables and functions */
#define  FDFS_STORAGE_STATUS_ACTIVE 136 
#define  FDFS_STORAGE_STATUS_DELETED 135 
#define  FDFS_STORAGE_STATUS_INIT 134 
#define  FDFS_STORAGE_STATUS_IP_CHANGED 133 
#define  FDFS_STORAGE_STATUS_OFFLINE 132 
#define  FDFS_STORAGE_STATUS_ONLINE 131 
#define  FDFS_STORAGE_STATUS_RECOVERY 130 
#define  FDFS_STORAGE_STATUS_SYNCING 129 
#define  FDFS_STORAGE_STATUS_WAIT_SYNC 128 

const char *get_storage_status_caption(const int status)
{
	switch (status)
	{
		case FDFS_STORAGE_STATUS_INIT:
			return "INIT";
		case FDFS_STORAGE_STATUS_WAIT_SYNC:
			return "WAIT_SYNC";
		case FDFS_STORAGE_STATUS_SYNCING:
			return "SYNCING";
		case FDFS_STORAGE_STATUS_OFFLINE:
			return "OFFLINE";
		case FDFS_STORAGE_STATUS_ONLINE:
			return "ONLINE";
		case FDFS_STORAGE_STATUS_DELETED:
			return "DELETED";
		case FDFS_STORAGE_STATUS_IP_CHANGED:
			return "IP_CHANGED";
		case FDFS_STORAGE_STATUS_ACTIVE:
			return "ACTIVE";
		case FDFS_STORAGE_STATUS_RECOVERY:
			return "RECOVERY";
		default:
			return "UNKOWN";
	}
}