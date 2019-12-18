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
typedef  int u32 ;

/* Variables and functions */

__attribute__((used)) static inline int mite_csigr_wpdep(u32 csigr_bits)
{				/*  write post fifo depth */
	unsigned int wpdep_bits = (csigr_bits >> 20) & 0x7;
	if (wpdep_bits == 0)
		return 0;
	else
		return 1 << (wpdep_bits - 1);
}