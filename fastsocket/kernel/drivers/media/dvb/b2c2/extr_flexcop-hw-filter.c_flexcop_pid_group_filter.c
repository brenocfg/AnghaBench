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
typedef  void* u16 ;
struct flexcop_device {int /*<<< orphan*/  (* write_ibi_reg ) (struct flexcop_device*,int /*<<< orphan*/ ,TYPE_2__) ;} ;
struct TYPE_4__ {void* Group_mask; void* Group_PID; } ;
struct TYPE_5__ {TYPE_1__ pid_filter_30c_ext_ind_0_7; } ;
typedef  TYPE_2__ flexcop_ibi_value ;

/* Variables and functions */
 int /*<<< orphan*/  pid_filter_30c ; 
 int /*<<< orphan*/  stub1 (struct flexcop_device*,int /*<<< orphan*/ ,TYPE_2__) ; 

__attribute__((used)) static void flexcop_pid_group_filter(struct flexcop_device *fc,
		u16 pid, u16 mask)
{
	/* index_reg_310.extra_index_reg need to 0 or 7 to work */
	flexcop_ibi_value v30c;
	v30c.pid_filter_30c_ext_ind_0_7.Group_PID = pid;
	v30c.pid_filter_30c_ext_ind_0_7.Group_mask = mask;
	fc->write_ibi_reg(fc, pid_filter_30c, v30c);
}