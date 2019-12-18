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
typedef  unsigned int u32 ;

/* Variables and functions */

__attribute__((used)) static inline void _transp(u32 d[], unsigned int i1, unsigned int i2,
			   unsigned int shift, u32 mask)
{
	u32 t = (d[i1] ^ (d[i2] >> shift)) & mask;

	d[i1] ^= t;
	d[i2] ^= t << shift;
}