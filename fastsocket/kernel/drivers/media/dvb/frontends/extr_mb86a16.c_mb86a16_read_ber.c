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
typedef  int u32 ;
struct mb86a16_state {int dummy; } ;
struct dvb_frontend {struct mb86a16_state* demodulator_priv; } ;

/* Variables and functions */
 int EREMOTEIO ; 
 int /*<<< orphan*/  MB86A16_BERLSB ; 
 int /*<<< orphan*/  MB86A16_BERMID ; 
 int /*<<< orphan*/  MB86A16_BERMON ; 
 int /*<<< orphan*/  MB86A16_BERMSB ; 
 int /*<<< orphan*/  MB86A16_BERTAB ; 
 int /*<<< orphan*/  MB86A16_DEBUG ; 
 int /*<<< orphan*/  MB86A16_ERROR ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,...) ; 
 int mb86a16_read (struct mb86a16_state*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  verbose ; 

__attribute__((used)) static int mb86a16_read_ber(struct dvb_frontend *fe, u32 *ber)
{
	u8 ber_mon, ber_tab, ber_lsb, ber_mid, ber_msb, ber_tim, ber_rst;
	u32 timer;

	struct mb86a16_state *state = fe->demodulator_priv;

	*ber = 0;
	if (mb86a16_read(state, MB86A16_BERMON, &ber_mon) != 2)
		goto err;
	if (mb86a16_read(state, MB86A16_BERTAB, &ber_tab) != 2)
		goto err;
	if (mb86a16_read(state, MB86A16_BERLSB, &ber_lsb) != 2)
		goto err;
	if (mb86a16_read(state, MB86A16_BERMID, &ber_mid) != 2)
		goto err;
	if (mb86a16_read(state, MB86A16_BERMSB, &ber_msb) != 2)
		goto err;
	/* BER monitor invalid when BER_EN = 0	*/
	if (ber_mon & 0x04) {
		/* coarse, fast calculation	*/
		*ber = ber_tab & 0x1f;
		dprintk(verbose, MB86A16_DEBUG, 1, "BER coarse=[0x%02x]", *ber);
		if (ber_mon & 0x01) {
			/*
			 * BER_SEL = 1, The monitored BER is the estimated
			 * value with a Reed-Solomon decoder error amount at
			 * the deinterleaver output.
			 * monitored BER is expressed as a 20 bit output in total
			 */
			ber_rst = ber_mon >> 3;
			*ber = (((ber_msb << 8) | ber_mid) << 8) | ber_lsb;
			if (ber_rst == 0)
				timer =  12500000;
			if (ber_rst == 1)
				timer =  25000000;
			if (ber_rst == 2)
				timer =  50000000;
			if (ber_rst == 3)
				timer = 100000000;

			*ber /= timer;
			dprintk(verbose, MB86A16_DEBUG, 1, "BER fine=[0x%02x]", *ber);
		} else {
			/*
			 * BER_SEL = 0, The monitored BER is the estimated
			 * value with a Viterbi decoder error amount at the
			 * QPSK demodulator output.
			 * monitored BER is expressed as a 24 bit output in total
			 */
			ber_tim = ber_mon >> 1;
			*ber = (((ber_msb << 8) | ber_mid) << 8) | ber_lsb;
			if (ber_tim == 0)
				timer = 16;
			if (ber_tim == 1)
				timer = 24;

			*ber /= 2 ^ timer;
			dprintk(verbose, MB86A16_DEBUG, 1, "BER fine=[0x%02x]", *ber);
		}
	}
	return 0;
err:
	dprintk(verbose, MB86A16_ERROR, 1, "I2C transfer error");
	return -EREMOTEIO;
}