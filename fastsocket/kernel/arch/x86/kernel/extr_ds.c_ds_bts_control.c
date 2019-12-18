#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int flags; } ;
struct TYPE_5__ {TYPE_1__ ds; } ;
struct bts_tracer {TYPE_2__ trace; } ;
struct TYPE_6__ {unsigned long* ctl; } ;

/* Variables and functions */
 int BTS_KERNEL ; 
 int BTS_USER ; 
 TYPE_3__ ds_cfg ; 
 size_t dsf_bts ; 
 size_t dsf_bts_kernel ; 
 size_t dsf_bts_user ; 

__attribute__((used)) static unsigned long ds_bts_control(struct bts_tracer *tracer)
{
	unsigned long control;

	control = ds_cfg.ctl[dsf_bts];
	if (!(tracer->trace.ds.flags & BTS_KERNEL))
		control |= ds_cfg.ctl[dsf_bts_kernel];
	if (!(tracer->trace.ds.flags & BTS_USER))
		control |= ds_cfg.ctl[dsf_bts_user];

	return control;
}