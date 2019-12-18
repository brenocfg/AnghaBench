#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct ix2505v_state {int frequency; TYPE_5__* config; } ;
struct TYPE_6__ {int symbol_rate; } ;
struct TYPE_7__ {TYPE_1__ qpsk; } ;
struct dvb_frontend_parameters {int frequency; TYPE_2__ u; } ;
struct TYPE_8__ {int frequency_min; int frequency_max; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* i2c_gate_ctrl ) (struct dvb_frontend*,int) ;TYPE_3__ info; } ;
struct dvb_frontend {TYPE_4__ ops; struct ix2505v_state* tuner_priv; } ;
typedef  int /*<<< orphan*/  data ;
struct TYPE_10__ {int tuner_gain; int tuner_chargepump; int min_delay_ms; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  deb_info (char*,int,int,...) ; 
 int ix2505v_write (struct ix2505v_state*,int*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  stub1 (struct dvb_frontend*,int) ; 
 int /*<<< orphan*/  stub2 (struct dvb_frontend*,int) ; 

__attribute__((used)) static int ix2505v_set_params(struct dvb_frontend *fe,
		struct dvb_frontend_parameters *params)
{
	struct ix2505v_state *state = fe->tuner_priv;
	u32 frequency = params->frequency;
	u32 b_w  = (params->u.qpsk.symbol_rate * 27) / 32000;
	u32 div_factor, N , A, x;
	int ret = 0, len;
	u8 gain, cc, ref, psc, local_osc, lpf;
	u8 data[4] = {0};

	if ((frequency < fe->ops.info.frequency_min)
	||  (frequency > fe->ops.info.frequency_max))
		return -EINVAL;

	if (state->config->tuner_gain)
		gain = (state->config->tuner_gain < 4)
			? state->config->tuner_gain : 0;
	else
		gain = 0x0;

	if (state->config->tuner_chargepump)
		cc = state->config->tuner_chargepump;
	else
		cc = 0x3;

	ref = 8; /* REF =1 */
	psc = 32; /* PSC = 0 */

	div_factor = (frequency * ref) / 40; /* local osc = 4Mhz */
	x = div_factor / psc;
	N = x/100;
	A = ((x - (N * 100)) * psc) / 100;

	data[0] = ((gain & 0x3) << 5) | (N >> 3);
	data[1] = (N << 5) | (A & 0x1f);
	data[2] = 0x81 | ((cc & 0x3) << 5) ; /*PD5,PD4 & TM = 0|C1,C0|REF=1*/

	deb_info("Frq=%d x=%d N=%d A=%d\n", frequency, x, N, A);

	if (frequency <= 1065000)
		local_osc = (6 << 5) | 2;
	else if (frequency <= 1170000)
		local_osc = (7 << 5) | 2;
	else if (frequency <= 1300000)
		local_osc = (1 << 5);
	else if (frequency <= 1445000)
		local_osc = (2 << 5);
	else if (frequency <= 1607000)
		local_osc = (3 << 5);
	else if (frequency <= 1778000)
		local_osc = (4 << 5);
	else if (frequency <= 1942000)
		local_osc = (5 << 5);
	else		/*frequency up to 2150000*/
		local_osc = (6 << 5);

	data[3] = local_osc; /* all other bits set 0 */

	if (b_w <= 10000)
		lpf = 0xc;
	else if (b_w <= 12000)
		lpf = 0x2;
	else if (b_w <= 14000)
		lpf = 0xa;
	else if (b_w <= 16000)
		lpf = 0x6;
	else if (b_w <= 18000)
		lpf = 0xe;
	else if (b_w <= 20000)
		lpf = 0x1;
	else if (b_w <= 22000)
		lpf = 0x9;
	else if (b_w <= 24000)
		lpf = 0x5;
	else if (b_w <= 26000)
		lpf = 0xd;
	else if (b_w <= 28000)
		lpf = 0x3;
		else
		lpf = 0xb;

	deb_info("Osc=%x b_w=%x lpf=%x\n", local_osc, b_w, lpf);
	deb_info("Data 0=[%x%x%x%x]\n", data[0], data[1], data[2], data[3]);

	if (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);

	len = sizeof(data);

	ret |= ix2505v_write(state, data, len);

	data[2] |= 0x4; /* set TM = 1 other bits same */

	len = 1;
	ret |= ix2505v_write(state, &data[2], len); /* write byte 4 only */

	msleep(10);

	data[2] |= ((lpf >> 2) & 0x3) << 3; /* lpf */
	data[3] |= (lpf & 0x3) << 2;

	deb_info("Data 2=[%x%x]\n", data[2], data[3]);

	len = 2;
	ret |= ix2505v_write(state, &data[2], len); /* write byte 4 & 5 */

	if (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0);

	if (state->config->min_delay_ms)
		msleep(state->config->min_delay_ms);

	state->frequency = frequency;

	return ret;
}