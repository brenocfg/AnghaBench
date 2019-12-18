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
typedef  int ssize_t ;
typedef  int off_t ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int lseek (int,int,int /*<<< orphan*/ ) ; 
 int read (int,void*,size_t) ; 

ssize_t
pread(int fd, void *buf, size_t len, off_t off) {
	off_t old;
	ssize_t rv;

	if ((old = lseek(fd, off, SEEK_SET)) == -1)
		return -1;

	if ((rv = read(fd, buf, len)) == -1)
		return -1;

	if (lseek(fd, old, SEEK_SET) == -1)
		return -1;

	return rv;
}