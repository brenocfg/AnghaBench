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
typedef  int /*<<< orphan*/  libzfs_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  bzero (char*,size_t) ; 
 int /*<<< orphan*/  no_memory (int /*<<< orphan*/ *) ; 
 void* realloc (void*,size_t) ; 

void *
zfs_realloc(libzfs_handle_t *hdl, void *ptr, size_t oldsize, size_t newsize)
{
	void *ret;

	if ((ret = realloc(ptr, newsize)) == NULL) {
		(void) no_memory(hdl);
		return (NULL);
	}

	bzero((char *)ret + oldsize, (newsize - oldsize));
	return (ret);
}