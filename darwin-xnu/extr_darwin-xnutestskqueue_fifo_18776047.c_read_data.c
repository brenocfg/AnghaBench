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
 scalar_t__ EAGAIN ; 
 int READ_BUFFER_LEN ; 
 int /*<<< orphan*/  T_ASSERT_FAIL (char*,int) ; 
 int /*<<< orphan*/  abort () ; 
 scalar_t__ errno ; 
 scalar_t__ read (int,char*,int) ; 

int
read_data(int fd)
{
	int retval, count = 0;
	char databuffer[READ_BUFFER_LEN];
	while (true) {
		errno  = 0;
		retval = (int)read(fd, databuffer, READ_BUFFER_LEN);
		if (retval < 0) {
			if (errno == EAGAIN) {
				return count;
			} else {
				T_ASSERT_FAIL("read from fd %d failed.", fd);
				abort();
			}
		}
		count += retval;
	}
}