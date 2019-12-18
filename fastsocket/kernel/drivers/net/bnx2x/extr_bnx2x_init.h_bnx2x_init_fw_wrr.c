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
typedef  size_t u32 ;
struct cmng_vnic {TYPE_1__* vnic_min_rate; } ;
struct TYPE_4__ {size_t fair_threshold; } ;
struct cmng_struct_per_port {TYPE_2__ fair_vars; } ;
struct cmng_init_input {scalar_t__* cos_min_rate; } ;
struct cmng_init {struct cmng_struct_per_port port; struct cmng_vnic vnic; } ;
struct TYPE_3__ {size_t* cos_credit_delta; } ;

/* Variables and functions */
 size_t BNX2X_PORT2_MODE_NUM_VNICS ; 
 size_t MAX_COS_NUMBER ; 
 size_t MIN_ABOVE_THRESH ; 
 int T_FAIR_COEF ; 

__attribute__((used)) static inline void bnx2x_init_fw_wrr(const struct cmng_init_input *input_data,
				     u32 r_param, struct cmng_init *ram_data)
{
	u32 vnic, cos;
	u32 cosWeightSum = 0;
	struct cmng_vnic *vdata = &ram_data->vnic;
	struct cmng_struct_per_port *pdata = &ram_data->port;

	for (cos = 0; cos < MAX_COS_NUMBER; cos++)
		cosWeightSum += input_data->cos_min_rate[cos];

	if (cosWeightSum > 0) {

		for (vnic = 0; vnic < BNX2X_PORT2_MODE_NUM_VNICS; vnic++) {
			/* Since cos and vnic shouldn't work together the rate
			 * to divide between the coses is the port rate.
			 */
			u32 *ccd = vdata->vnic_min_rate[vnic].cos_credit_delta;
			for (cos = 0; cos < MAX_COS_NUMBER; cos++) {
				/* this is the credit for each period of
				 * the fairness algorithm - number of bytes
				 * in T_FAIR (this cos share of the vnic rate)
				 */
				ccd[cos] =
				    (u32)input_data->cos_min_rate[cos] * 100 *
				    (T_FAIR_COEF / (8 * 100 * cosWeightSum));
				 if (ccd[cos] < pdata->fair_vars.fair_threshold
						+ MIN_ABOVE_THRESH) {
					ccd[cos] =
					    pdata->fair_vars.fair_threshold +
					    MIN_ABOVE_THRESH;
				}
			}
		}
	}
}