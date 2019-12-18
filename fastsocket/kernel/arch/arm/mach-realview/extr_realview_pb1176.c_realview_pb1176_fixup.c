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
struct tag {int dummy; } ;
struct meminfo {int nr_banks; TYPE_1__* bank; } ;
struct machine_desc {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  size; scalar_t__ start; } ;

/* Variables and functions */
 int /*<<< orphan*/  SZ_128M ; 

__attribute__((used)) static void realview_pb1176_fixup(struct machine_desc *mdesc,
				  struct tag *tags, char **from,
				  struct meminfo *meminfo)
{
	/*
	 * RealView PB1176 only has 128MB of RAM mapped at 0.
	 */
	meminfo->bank[0].start = 0;
	meminfo->bank[0].size = SZ_128M;
	meminfo->nr_banks = 1;
}