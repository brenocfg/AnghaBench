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
struct TYPE_4__ {size_t fair_threshold; size_t upper_bound; size_t fairness_timeout; } ;
struct cmng_struct_per_port {TYPE_2__ fair_vars; } ;
struct cmng_init_input {int port_rate; scalar_t__* vnic_min_rate; } ;
struct cmng_init {struct cmng_struct_per_port port; struct cmng_vnic vnic; } ;
struct TYPE_3__ {size_t vn_credit_delta; } ;

/* Variables and functions */
 size_t BNX2X_PORT2_MODE_NUM_VNICS ; 
 size_t FAIR_MEM ; 
 size_t MIN_ABOVE_THRESH ; 
 size_t QM_ARB_BYTES ; 
 size_t SDM_TICKS ; 
 int T_FAIR_COEF ; 

__attribute__((used)) static inline void bnx2x_init_min(const struct cmng_init_input *input_data,
				  u32 r_param, struct cmng_init *ram_data)
{
	u32 vnic, fair_periodic_timeout_usec, vnicWeightSum, tFair;
	struct cmng_vnic *vdata = &ram_data->vnic;
	struct cmng_struct_per_port *pdata = &ram_data->port;

	/* this is the resolution of the fairness timer */
	fair_periodic_timeout_usec = QM_ARB_BYTES / r_param;

	/* fairness per-port variables
	 * for 10G it is 1000usec. for 1G it is 10000usec.
	 */
	tFair = T_FAIR_COEF / input_data->port_rate;

	/* this is the threshold below which we won't arm the timer anymore */
	pdata->fair_vars.fair_threshold = QM_ARB_BYTES;

	/* we multiply by 1e3/8 to get bytes/msec. We don't want the credits
	 * to pass a credit of the T_FAIR*FAIR_MEM (algorithm resolution)
	 */
	pdata->fair_vars.upper_bound = r_param * tFair * FAIR_MEM;

	/* since each tick is 4 microSeconds */
	pdata->fair_vars.fairness_timeout =
				fair_periodic_timeout_usec / SDM_TICKS;

	/* calculate sum of weights */
	vnicWeightSum = 0;

	for (vnic = 0; vnic < BNX2X_PORT2_MODE_NUM_VNICS; vnic++)
		vnicWeightSum += input_data->vnic_min_rate[vnic];

	/* global vnic counter */
	if (vnicWeightSum > 0) {
		/* fairness per-vnic variables */
		for (vnic = 0; vnic < BNX2X_PORT2_MODE_NUM_VNICS; vnic++) {
			/* this is the credit for each period of the fairness
			 * algorithm - number of bytes in T_FAIR (this vnic
			 * share of the port rate)
			 */
			vdata->vnic_min_rate[vnic].vn_credit_delta =
				(u32)input_data->vnic_min_rate[vnic] * 100 *
				(T_FAIR_COEF / (8 * 100 * vnicWeightSum));
			if (vdata->vnic_min_rate[vnic].vn_credit_delta <
			    pdata->fair_vars.fair_threshold +
			    MIN_ABOVE_THRESH) {
				vdata->vnic_min_rate[vnic].vn_credit_delta =
					pdata->fair_vars.fair_threshold +
					MIN_ABOVE_THRESH;
			}
		}
	}
}