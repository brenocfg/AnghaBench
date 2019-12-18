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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct TYPE_2__ {int size; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  hw_awrite (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ hw_bank ; 

__attribute__((used)) static int hw_register_write(u16 addr, u32 data)
{
	/* align */
	addr /= sizeof(u32);

	if (addr >= hw_bank.size)
		return -EINVAL;

	/* align */
	addr *= sizeof(u32);

	hw_awrite(addr, ~0, data);
	return 0;
}