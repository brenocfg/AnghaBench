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
typedef  int u32 ;
struct mem_ctl_info {struct amd64_pvt* pvt_info; } ;
struct amd64_pvt {int /*<<< orphan*/  F3; } ;
struct TYPE_2__ {int x86; } ;

/* Variables and functions */
 int __amd64_set_scrub_rate (int /*<<< orphan*/ ,int,int) ; 
 TYPE_1__ boot_cpu_data ; 
 int /*<<< orphan*/  f15h_select_dct (struct amd64_pvt*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int amd64_set_scrub_rate(struct mem_ctl_info *mci, u32 bw)
{
	struct amd64_pvt *pvt = mci->pvt_info;
	u32 min_scrubrate = 0x5;

	if (boot_cpu_data.x86 == 0xf)
		min_scrubrate = 0x0;

	/* F15h Erratum #505 */
	if (boot_cpu_data.x86 == 0x15)
		f15h_select_dct(pvt, 0);

	return __amd64_set_scrub_rate(pvt->F3, bw, min_scrubrate);
}