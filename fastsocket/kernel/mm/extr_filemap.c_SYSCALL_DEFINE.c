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
struct file {int f_mode; struct address_space* f_mapping; } ;
struct address_space {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int pgoff_t ;
typedef  size_t loff_t ;
typedef  int /*<<< orphan*/  SYSCALL_DEFINE ;

/* Variables and functions */
 int /*<<< orphan*/  EBADF ; 
 int FMODE_READ ; 
 size_t PAGE_CACHE_SHIFT ; 
 int /*<<< orphan*/  do_readahead (struct address_space*,struct file*,int,unsigned long) ; 
 struct file* fget (int) ; 
 int /*<<< orphan*/  fput (struct file*) ; 

SYSCALL_DEFINE(readahead)(int fd, loff_t offset, size_t count)
{
	ssize_t ret;
	struct file *file;

	ret = -EBADF;
	file = fget(fd);
	if (file) {
		if (file->f_mode & FMODE_READ) {
			struct address_space *mapping = file->f_mapping;
			pgoff_t start = offset >> PAGE_CACHE_SHIFT;
			pgoff_t end = (offset + count - 1) >> PAGE_CACHE_SHIFT;
			unsigned long len = end - start + 1;
			ret = do_readahead(mapping, file, start, len);
		}
		fput(file);
	}
	return ret;
}