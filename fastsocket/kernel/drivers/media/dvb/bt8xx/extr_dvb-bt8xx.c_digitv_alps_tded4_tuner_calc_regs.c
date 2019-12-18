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
typedef  int u8 ;
typedef  int u32 ;
struct dvb_ofdm_parameters {int bandwidth; } ;
struct TYPE_2__ {struct dvb_ofdm_parameters ofdm; } ;
struct dvb_frontend_parameters {int frequency; TYPE_1__ u; } ;
struct dvb_frontend {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int IF_FREQUENCYx6 ; 
 int /*<<< orphan*/  dprintk (char*,int,int) ; 

__attribute__((used)) static int digitv_alps_tded4_tuner_calc_regs(struct dvb_frontend* fe, struct dvb_frontend_parameters* params, u8* pllbuf, int buf_len)
{
	u32 div;
	struct dvb_ofdm_parameters *op = &params->u.ofdm;

	if (buf_len < 5)
		return -EINVAL;

	div = (((params->frequency + 83333) * 3) / 500000) + IF_FREQUENCYx6;

	pllbuf[0] = 0x61;
	pllbuf[1] = (div >> 8) & 0x7F;
	pllbuf[2] = div & 0xFF;
	pllbuf[3] = 0x85;

	dprintk("frequency %u, div %u\n", params->frequency, div);

	if (params->frequency < 470000000)
		pllbuf[4] = 0x02;
	else if (params->frequency > 823000000)
		pllbuf[4] = 0x88;
	else
		pllbuf[4] = 0x08;

	if (op->bandwidth == 8)
		pllbuf[4] |= 0x04;

	return 5;
}