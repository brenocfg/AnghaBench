#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nasid_t ;
typedef  int /*<<< orphan*/  lboard_t ;
typedef  int /*<<< orphan*/  klinfo_t ;
struct TYPE_4__ {int physid; } ;
struct TYPE_5__ {TYPE_1__ cpu_info; } ;
typedef  TYPE_2__ klcpu_t ;

/* Variables and functions */
 int /*<<< orphan*/  KLSTRUCT_CPU ; 
 int /*<<< orphan*/  KLTYPE_IP27 ; 
 scalar_t__ KL_CONFIG_INFO (int /*<<< orphan*/ ) ; 
 scalar_t__ find_component (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ find_first_component (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * find_lboard (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

klcpu_t * nasid_slice_to_cpuinfo(nasid_t nasid, int slice)
{
	lboard_t *brd;
	klcpu_t *acpu;

	if (!(brd = find_lboard((lboard_t *)KL_CONFIG_INFO(nasid), KLTYPE_IP27)))
		return (klcpu_t *)NULL;

	if (!(acpu = (klcpu_t *)find_first_component(brd, KLSTRUCT_CPU)))
		return (klcpu_t *)NULL;

	do {
		if ((acpu->cpu_info.physid) == slice)
			return acpu;
	} while ((acpu = (klcpu_t *)find_component(brd, (klinfo_t *)acpu,
								KLSTRUCT_CPU)));
	return (klcpu_t *)NULL;
}