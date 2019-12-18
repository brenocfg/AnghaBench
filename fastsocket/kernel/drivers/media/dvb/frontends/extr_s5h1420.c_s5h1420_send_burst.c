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
struct s5h1420_state {int dummy; } ;
struct dvb_frontend {struct s5h1420_state* demodulator_priv; } ;
typedef  scalar_t__ fe_sec_mini_cmd_t ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int HZ ; 
 scalar_t__ SEC_MINI_B ; 
 int jiffies ; 
 int /*<<< orphan*/  msleep (int) ; 
 int s5h1420_readreg (struct s5h1420_state*,int) ; 
 int /*<<< orphan*/  s5h1420_writereg (struct s5h1420_state*,int,int) ; 
 scalar_t__ time_after (int,unsigned long) ; 
 scalar_t__ time_before (int,unsigned long) ; 

__attribute__((used)) static int s5h1420_send_burst (struct dvb_frontend* fe, fe_sec_mini_cmd_t minicmd)
{
	struct s5h1420_state* state = fe->demodulator_priv;
	u8 val;
	int result = 0;
	unsigned long timeout;

	/* setup for tone burst */
	val = s5h1420_readreg(state, 0x3b);
	s5h1420_writereg(state, 0x3b, (s5h1420_readreg(state, 0x3b) & 0x70) | 0x01);

	/* set value for B position if requested */
	if (minicmd == SEC_MINI_B) {
		s5h1420_writereg(state, 0x3b, s5h1420_readreg(state, 0x3b) | 0x04);
	}
	msleep(15);

	/* start transmission */
	s5h1420_writereg(state, 0x3b, s5h1420_readreg(state, 0x3b) | 0x08);

	/* wait for transmission to complete */
	timeout = jiffies + ((100*HZ) / 1000);
	while(time_before(jiffies, timeout)) {
		if (!(s5h1420_readreg(state, 0x3b) & 0x08))
			break;

		msleep(5);
	}
	if (time_after(jiffies, timeout))
		result = -ETIMEDOUT;

	/* restore original settings */
	s5h1420_writereg(state, 0x3b, val);
	msleep(15);
	return result;
}