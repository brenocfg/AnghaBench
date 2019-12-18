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
struct dvb_frontend {struct dtt200u_fe_state* demodulator_priv; } ;
struct dtt200u_fe_state {int /*<<< orphan*/  d; } ;

/* Variables and functions */
 int GET_VIT_ERR_CNT ; 
 int /*<<< orphan*/  dvb_usb_generic_rw (int /*<<< orphan*/ ,int*,int,int*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dtt200u_fe_read_ber(struct dvb_frontend* fe, u32 *ber)
{
	struct dtt200u_fe_state *state = fe->demodulator_priv;
	u8 bw = GET_VIT_ERR_CNT,b[3];
	dvb_usb_generic_rw(state->d,&bw,1,b,3,0);
	*ber = (b[0] << 16) | (b[1] << 8) | b[2];
	return 0;
}