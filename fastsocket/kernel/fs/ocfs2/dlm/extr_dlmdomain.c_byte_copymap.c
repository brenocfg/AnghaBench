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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int /*<<< orphan*/  byte_set_bit (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ test_bit (unsigned int,unsigned long*) ; 

__attribute__((used)) static inline void byte_copymap(u8 dmap[], unsigned long smap[],
			unsigned int sz)
{
	unsigned int nn;

	if (!sz)
		return;

	memset(dmap, 0, ((sz + 7) >> 3));
	for (nn = 0 ; nn < sz; nn++)
		if (test_bit(nn, smap))
			byte_set_bit(nn, dmap);
}