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
typedef  int u32 ;
typedef  int /*<<< orphan*/  loff_t ;
typedef  int /*<<< orphan*/  SYSCALL_DEFINE ;

/* Variables and functions */
 int /*<<< orphan*/  sys_fallocate (int,int,int /*<<< orphan*/ ,int) ; 

SYSCALL_DEFINE(s390_fallocate)(int fd, int mode, loff_t offset,
			       u32 len_high, u32 len_low)
{
	return sys_fallocate(fd, mode, offset, ((u64)len_high << 32) | len_low);
}