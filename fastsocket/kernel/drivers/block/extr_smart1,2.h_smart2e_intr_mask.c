#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ io_mem_addr; } ;
typedef  TYPE_1__ ctlr_info_t ;

/* Variables and functions */
 scalar_t__ INTR_MASK ; 
 int /*<<< orphan*/  outl (unsigned long,scalar_t__) ; 

__attribute__((used)) static void smart2e_intr_mask(ctlr_info_t *h, unsigned long val)
{
	outl(val, h->io_mem_addr + INTR_MASK);
}