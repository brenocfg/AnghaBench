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
typedef  int u8 ;
struct dvb_frontend {struct af9005_fe_state* demodulator_priv; } ;
struct af9005_fe_state {int /*<<< orphan*/  d; } ;

/* Variables and functions */
 int af9005_read_register_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  fec_vtb_rsd_mon_en_len ; 
 int /*<<< orphan*/  fec_vtb_rsd_mon_en_pos ; 
 int /*<<< orphan*/  reg_ofsm_read_rbc_en_len ; 
 int /*<<< orphan*/  reg_ofsm_read_rbc_en_pos ; 
 int /*<<< orphan*/  xd_p_fec_vtb_rsd_mon_en ; 
 int /*<<< orphan*/  xd_p_reg_ofsm_read_rbc_en ; 

__attribute__((used)) static int af9005_is_fecmon_available(struct dvb_frontend *fe, int *available)
{
	struct af9005_fe_state *state = fe->demodulator_priv;
	int ret;
	u8 temp;

	*available = false;

	ret = af9005_read_register_bits(state->d, xd_p_fec_vtb_rsd_mon_en,
					fec_vtb_rsd_mon_en_pos,
					fec_vtb_rsd_mon_en_len, &temp);
	if (ret)
		return ret;
	if (temp & 1) {
		ret =
		    af9005_read_register_bits(state->d,
					      xd_p_reg_ofsm_read_rbc_en,
					      reg_ofsm_read_rbc_en_pos,
					      reg_ofsm_read_rbc_en_len, &temp);
		if (ret)
			return ret;
		if ((temp & 1) == 0)
			*available = true;

	}
	return 0;
}