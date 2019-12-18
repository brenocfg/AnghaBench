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
typedef  int /*<<< orphan*/  __u64 ;

/* Variables and functions */
 int pread (int,char*,int,int /*<<< orphan*/ ) ; 

int file_reader(__u64 offset, char *buf, int len, void *arg)
{
	int fd = *((int *) arg);

	return pread(fd, buf, len, offset);
}