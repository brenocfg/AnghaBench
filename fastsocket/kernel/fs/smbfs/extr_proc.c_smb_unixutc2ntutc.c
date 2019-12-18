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
typedef  int u64 ;
struct timespec {int tv_nsec; scalar_t__ tv_sec; } ;

/* Variables and functions */
 int NTFS_TIME_OFFSET ; 

__attribute__((used)) static u64
smb_unixutc2ntutc(struct timespec ts)
{
	/* Note: timezone conversion is probably wrong. */
	/* return ((u64)utc2local(server, t)) * 10000000 + NTFS_TIME_OFFSET; */
	return ((u64)ts.tv_sec) * 10000000 + ts.tv_nsec/100 + NTFS_TIME_OFFSET;
}