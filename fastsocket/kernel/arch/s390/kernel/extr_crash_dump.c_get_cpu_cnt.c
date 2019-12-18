#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ pref_reg; } ;
struct TYPE_4__ {TYPE_1__ s390x; } ;

/* Variables and functions */
 TYPE_2__** zfcpdump_save_areas ; 

__attribute__((used)) static int get_cpu_cnt(void)
{
	int i, cpus = 0;

	for (i = 0; zfcpdump_save_areas[i]; i++) {
		if (zfcpdump_save_areas[i]->s390x.pref_reg == 0)
			continue;
		cpus++;
	}
	return cpus;
}