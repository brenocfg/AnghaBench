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

__attribute__((used)) static unsigned int u4_pcie_cfa1(unsigned int bus, unsigned int devfn,
				 unsigned int off)
{
        return (bus << 16)		|
	       (devfn << 8)		|
	       ((off >> 8) << 28)	|
	       (off & 0xfcu)		| 1u;
}