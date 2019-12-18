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

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  bcopy (char*,void*,int) ; 

__attribute__((used)) static int
attrlist_unpack_fixed(char **cursor, char *end, void *buf, ssize_t size)
{
	/* make sure we have enough source data */
	if ((*cursor) + size > end)
		return(EINVAL);

	bcopy(*cursor, buf, size);
	*cursor += size;
	return(0);
}