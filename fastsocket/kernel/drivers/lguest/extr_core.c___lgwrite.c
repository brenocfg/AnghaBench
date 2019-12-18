#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct lg_cpu {TYPE_1__* lg; } ;
struct TYPE_2__ {scalar_t__ mem_base; } ;

/* Variables and functions */
 scalar_t__ copy_to_user (scalar_t__,void const*,unsigned int) ; 
 int /*<<< orphan*/  kill_guest (struct lg_cpu*,char*,unsigned long,unsigned int) ; 
 int /*<<< orphan*/  lguest_address_ok (TYPE_1__*,unsigned long,unsigned int) ; 

void __lgwrite(struct lg_cpu *cpu, unsigned long addr, const void *b,
	       unsigned bytes)
{
	if (!lguest_address_ok(cpu->lg, addr, bytes)
	    || copy_to_user(cpu->lg->mem_base + addr, b, bytes) != 0)
		kill_guest(cpu, "bad write address %#lx len %u", addr, bytes);
}