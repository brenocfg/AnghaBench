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
 int /*<<< orphan*/  OPENFLAGS () ; 
 int /*<<< orphan*/  STUB_CODE ; 
 int /*<<< orphan*/  STUB_DATA ; 
 int map_stub_pages (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  of_cloexec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_write (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_close_file (int) ; 
 int os_open_file (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ skas_needs_stub ; 

int new_mm(unsigned long stack)
{
	int fd, err;

	fd = os_open_file("/proc/mm", of_cloexec(of_write(OPENFLAGS())), 0);
	if (fd < 0)
		return fd;

	if (skas_needs_stub) {
		err = map_stub_pages(fd, STUB_CODE, STUB_DATA, stack);
		if (err) {
			os_close_file(fd);
			return err;
		}
	}

	return fd;
}