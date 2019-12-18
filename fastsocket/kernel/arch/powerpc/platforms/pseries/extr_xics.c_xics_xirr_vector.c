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

__attribute__((used)) static inline unsigned int xics_xirr_vector(unsigned int xirr)
{
	/*
	 * The top byte is the old cppr, to be restored on EOI.
	 * The remaining 24 bits are the vector.
	 */
	return xirr & 0x00ffffff;
}