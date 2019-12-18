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
typedef  enum vpss_ccdc_source_sel { ____Placeholder_vpss_ccdc_source_sel } vpss_ccdc_source_sel ;
struct TYPE_3__ {int /*<<< orphan*/  select_ccdc_source; } ;
struct TYPE_4__ {TYPE_1__ hw_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  dm355_select_ccdc_source (int) ; 
 TYPE_2__ oper_cfg ; 

int vpss_select_ccdc_source(enum vpss_ccdc_source_sel src_sel)
{
	if (!oper_cfg.hw_ops.select_ccdc_source)
		return -1;

	dm355_select_ccdc_source(src_sel);
	return 0;
}