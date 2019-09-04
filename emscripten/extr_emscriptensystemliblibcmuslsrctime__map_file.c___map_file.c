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
struct stat {size_t st_size; } ;

/* Variables and functions */
 unsigned char const* MAP_FAILED ; 
 int /*<<< orphan*/  MAP_SHARED ; 
 int O_CLOEXEC ; 
 int O_NONBLOCK ; 
 int O_RDONLY ; 
 int /*<<< orphan*/  PROT_READ ; 
 int /*<<< orphan*/  SYS_close ; 
 int /*<<< orphan*/  SYS_fstat ; 
 unsigned char* __mmap (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int __sys_open (char const*,int) ; 
 int /*<<< orphan*/  __syscall (int /*<<< orphan*/ ,int,...) ; 

const char unsigned *__map_file(const char *pathname, size_t *size)
{
	struct stat st;
	const unsigned char *map = MAP_FAILED;
	int fd = __sys_open(pathname, O_RDONLY|O_CLOEXEC|O_NONBLOCK);
	if (fd < 0) return 0;
	if (!__syscall(SYS_fstat, fd, &st)) {
		map = __mmap(0, st.st_size, PROT_READ, MAP_SHARED, fd, 0);
		*size = st.st_size;
	}
	__syscall(SYS_close, fd);
	return map == MAP_FAILED ? 0 : map;
}