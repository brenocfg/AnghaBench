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
typedef  scalar_t__ u64 ;
struct timespec {int tv_nsec; scalar_t__ tv_sec; } ;

/* Variables and functions */
 scalar_t__ NTFS_TIME_OFFSET ; 
 int do_div (scalar_t__,int) ; 

__attribute__((used)) static struct timespec
smb_ntutc2unixutc(u64 ntutc)
{
	struct timespec ts;
	/* FIXME: what about the timezone difference? */
	/* Subtract the NTFS time offset, then convert to 1s intervals. */
	u64 t = ntutc - NTFS_TIME_OFFSET;
	ts.tv_nsec = do_div(t, 10000000) * 100;
	ts.tv_sec = t; 
	return ts;
}