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
struct dvb_frontend {struct dib3000_state* demodulator_priv; } ;
struct dib3000_state {int dummy; } ;

/* Variables and functions */
 scalar_t__ DIB3000MB_REG_FIRST_PID ; 
 int DIB3000_ACTIVATE_PID_FILTERING ; 
 int /*<<< orphan*/  wr (scalar_t__,int) ; 

__attribute__((used)) static int dib3000mb_pid_control(struct dvb_frontend *fe,int index, int pid,int onoff)
{
	struct dib3000_state *state = fe->demodulator_priv;
	pid = (onoff ? pid | DIB3000_ACTIVATE_PID_FILTERING : 0);
	wr(index+DIB3000MB_REG_FIRST_PID,pid);
	return 0;
}