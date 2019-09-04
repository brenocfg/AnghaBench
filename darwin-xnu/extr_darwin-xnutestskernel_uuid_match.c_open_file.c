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
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 void* MAP_FAILED ; 
 int /*<<< orphan*/  MAP_PRIVATE ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  PROT_READ ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ lseek (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* mmap (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int open (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *open_file(char *path, size_t *len) {
	int fd;
	if ((fd = open(path, O_RDONLY)) < 0) {
		return NULL;
	}
	*len = (size_t)lseek(fd, (off_t)0, SEEK_END);
	void *p = mmap(NULL, *len, PROT_READ, MAP_PRIVATE, fd, 0);
	close(fd);
	if (p == MAP_FAILED) {
		return NULL;
	}
	return p;
}