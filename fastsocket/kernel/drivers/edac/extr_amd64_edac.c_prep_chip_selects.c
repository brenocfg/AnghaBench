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
struct amd64_pvt {scalar_t__ ext_model; TYPE_1__* csels; } ;
struct TYPE_4__ {int x86; } ;
struct TYPE_3__ {int b_cnt; int m_cnt; } ;

/* Variables and functions */
 scalar_t__ K8_REV_F ; 
 TYPE_2__ boot_cpu_data ; 

__attribute__((used)) static void prep_chip_selects(struct amd64_pvt *pvt)
{
	if (boot_cpu_data.x86 == 0xf && pvt->ext_model < K8_REV_F) {
		pvt->csels[0].b_cnt = pvt->csels[1].b_cnt = 8;
		pvt->csels[0].m_cnt = pvt->csels[1].m_cnt = 8;
	} else {
		pvt->csels[0].b_cnt = pvt->csels[1].b_cnt = 8;
		pvt->csels[0].m_cnt = pvt->csels[1].m_cnt = 4;
	}
}