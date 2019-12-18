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
struct TYPE_4__ {int /*<<< orphan*/  wb_exp_stats_op_buf; } ;
typedef  TYPE_2__ vfe_msg_stats_wb_exp ;
struct msm_adsp_module {int dummy; } ;
struct TYPE_3__ {scalar_t__ msg16; } ;
struct adsp_event {TYPE_1__ data; } ;

/* Variables and functions */
 int adsp_pmem_paddr_fixup (struct msm_adsp_module*,void**) ; 

__attribute__((used)) static int patch_af_wb_event(struct msm_adsp_module *module,
				struct adsp_event *event)
{
	vfe_msg_stats_wb_exp *af = (vfe_msg_stats_wb_exp *)event->data.msg16;
	return adsp_pmem_paddr_fixup(module, (void **)&af->wb_exp_stats_op_buf);
}