#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct clk {int dummy; } ;
typedef  enum msm_camio_clk_src_type { ____Placeholder_msm_camio_clk_src_type } msm_camio_clk_src_type ;

/* Variables and functions */
#define  MSM_CAMIO_CLK_SRC_EXTERNAL 129 
#define  MSM_CAMIO_CLK_SRC_INTERNAL 128 
 struct clk* camio_vfe_clk ; 
 int /*<<< orphan*/  clk_set_flags (struct clk*,int) ; 

void msm_camio_clk_sel(enum msm_camio_clk_src_type srctype)
{
	struct clk *clk = NULL;

	clk = camio_vfe_clk;

	if (clk != NULL) {
		switch (srctype) {
		case MSM_CAMIO_CLK_SRC_INTERNAL:
			clk_set_flags(clk, 0x00000100 << 1);
			break;

		case MSM_CAMIO_CLK_SRC_EXTERNAL:
			clk_set_flags(clk, 0x00000100);
			break;

		default:
			break;
		}
	}
}