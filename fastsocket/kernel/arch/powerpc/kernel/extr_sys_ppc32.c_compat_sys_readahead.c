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
typedef  int u32 ;
typedef  int loff_t ;
typedef  int /*<<< orphan*/  compat_ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  sys_readahead (int,int,int) ; 

compat_ssize_t compat_sys_readahead(int fd, u32 r4, u32 offhi, u32 offlo, u32 count)
{
	return sys_readahead(fd, ((loff_t)offhi << 32) | offlo, count);
}