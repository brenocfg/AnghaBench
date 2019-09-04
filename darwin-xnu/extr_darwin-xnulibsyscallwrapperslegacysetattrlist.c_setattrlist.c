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
 scalar_t__ ENOTSUP ; 
 scalar_t__ EOPNOTSUPP ; 
 int __setattrlist (char const*,void*,void*,size_t,unsigned int) ; 
 scalar_t__ errno ; 

int
#ifdef __LP64__
setattrlist(const char *path, void *attrList, void *attrBuf,
	size_t attrBufSize, unsigned int options)
#else /* !__LP64__ */
setattrlist(const char *path, void *attrList, void *attrBuf,
	size_t attrBufSize, unsigned long options)
#endif /* __LP64__ */
{
	int ret = __setattrlist(path, attrList, attrBuf, attrBufSize, options);

	/* use ENOTSUP for legacy behavior */
	if (ret < 0 && errno == EOPNOTSUPP)
		errno = ENOTSUP;
	return ret;
}