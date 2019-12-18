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
typedef  enum vpss_wbl_sel { ____Placeholder_vpss_wbl_sel } vpss_wbl_sel ;
struct TYPE_3__ {int (* clear_wbl_overflow ) (int) ;} ;
struct TYPE_4__ {TYPE_1__ hw_ops; } ;

/* Variables and functions */
 TYPE_2__ oper_cfg ; 
 int stub1 (int) ; 

int vpss_clear_wbl_overflow(enum vpss_wbl_sel wbl_sel)
{
	if (!oper_cfg.hw_ops.clear_wbl_overflow)
		return -1;

	return oper_cfg.hw_ops.clear_wbl_overflow(wbl_sel);
}