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
typedef  int u_int ;

/* Variables and functions */

__attribute__((used)) static inline void set_mdcas(u_int *mdcas, int delayed, u_int rcd)
{
	u_int shift;

	rcd = 2 * rcd - 1;
	shift = delayed + 1 + rcd;

	mdcas[0]  = (1 << rcd) - 1;
	mdcas[0] |= 0x55555555 << shift;
	mdcas[1]  = mdcas[2] = 0x55555555 << (shift & 1);
}