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
struct TYPE_2__ {int /*<<< orphan*/ * wb_exp_stats_op_buf; } ;
typedef  TYPE_1__ vfe_cmd_stats_wb_exp_cfg ;
struct msm_adsp_module {int dummy; } ;

/* Variables and functions */
 scalar_t__ adsp_pmem_fixup (struct msm_adsp_module*,void**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  awb_size ; 

__attribute__((used)) static inline int verify_cmd_stats_wb_exp_cfg(struct msm_adsp_module *module,
					      void *cmd_data, size_t cmd_size)
{
	vfe_cmd_stats_wb_exp_cfg *cmd =
		(vfe_cmd_stats_wb_exp_cfg *)cmd_data;
	int i;

	if (cmd_size != sizeof(vfe_cmd_stats_wb_exp_cfg))
		return -1;

	for (i = 0; i < 3; i++) {
		void **addr = (void **)(&cmd->wb_exp_stats_op_buf[i]);
		if (*addr && adsp_pmem_fixup(module, addr, awb_size))
			return -1;
	}
	return 0;
}