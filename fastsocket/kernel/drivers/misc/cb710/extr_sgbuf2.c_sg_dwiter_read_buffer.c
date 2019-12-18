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
typedef  int /*<<< orphan*/  uint32_t ;
struct sg_mapping_iter {scalar_t__ consumed; scalar_t__ addr; scalar_t__ length; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (void*,scalar_t__,size_t) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,size_t) ; 
 size_t min (scalar_t__,size_t) ; 
 scalar_t__ sg_dwiter_next (struct sg_mapping_iter*) ; 

__attribute__((used)) static uint32_t sg_dwiter_read_buffer(struct sg_mapping_iter *miter)
{
	size_t len, left = 4;
	uint32_t data;
	void *addr = &data;

	do {
		len = min(miter->length - miter->consumed, left);
		memcpy(addr, miter->addr + miter->consumed, len);
		miter->consumed += len;
		left -= len;
		if (!left)
			return data;
		addr += len;
	} while (sg_dwiter_next(miter));

	memset(addr, 0, left);
	return data;
}