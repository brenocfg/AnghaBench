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
struct fuse_copy_state {unsigned int len; void* buf; scalar_t__ write; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (void*,void*,unsigned int) ; 
 unsigned int min (unsigned int,unsigned int) ; 

__attribute__((used)) static int fuse_copy_do(struct fuse_copy_state *cs, void **val, unsigned *size)
{
	unsigned ncpy = min(*size, cs->len);
	if (val) {
		if (cs->write)
			memcpy(cs->buf, *val, ncpy);
		else
			memcpy(*val, cs->buf, ncpy);
		*val += ncpy;
	}
	*size -= ncpy;
	cs->len -= ncpy;
	cs->buf += ncpy;
	return ncpy;
}