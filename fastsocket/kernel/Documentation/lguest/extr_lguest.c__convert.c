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
struct iovec {size_t iov_len; void* iov_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  errx (int,char*,void*,char const*) ; 

__attribute__((used)) static void *_convert(struct iovec *iov, size_t size, size_t align,
		      const char *name)
{
	if (iov->iov_len != size)
		errx(1, "Bad iovec size %zu for %s", iov->iov_len, name);
	if ((unsigned long)iov->iov_base % align != 0)
		errx(1, "Bad alignment %p for %s", iov->iov_base, name);
	return iov->iov_base;
}