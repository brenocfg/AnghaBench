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
struct TYPE_2__ {unsigned int addr_data; int regspacing; int /*<<< orphan*/  regsize; } ;
struct smi_info {int io_size; TYPE_1__ io; } ;

/* Variables and functions */
 int /*<<< orphan*/  release_region (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void port_cleanup(struct smi_info *info)
{
	unsigned int addr = info->io.addr_data;
	int          idx;

	if (addr) {
		for (idx = 0; idx < info->io_size; idx++)
			release_region(addr + idx * info->io.regspacing,
				       info->io.regsize);
	}
}