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
struct mac_iop {int ram_addr_lo; int ram_addr_hi; int /*<<< orphan*/  ram_data; } ;
typedef  int /*<<< orphan*/  __u8 ;
typedef  int __u16 ;

/* Variables and functions */

__attribute__((used)) static __inline__ void iop_writeb(volatile struct mac_iop *iop, __u16 addr, __u8 data)
{
	iop->ram_addr_lo = addr;
	iop->ram_addr_hi = addr >> 8;
	iop->ram_data = data;
}