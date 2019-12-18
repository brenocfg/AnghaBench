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
struct _pid {int setpoint; scalar_t__ deadband; int p_gain; int integral; int d_gain; int last_err; int i_gain; } ;
typedef  int int32_t ;

/* Variables and functions */
 scalar_t__ abs (int) ; 
 scalar_t__ fp_toint (int) ; 
 int int_tofp (int) ; 
 int mul_fp (int,int) ; 

__attribute__((used)) static signed int pid_calc(struct _pid *pid, int busy)
{
	signed int err, result;
	int32_t pterm, dterm, fp_error;
	int32_t integral_limit;

	err = pid->setpoint - busy;
	fp_error = int_tofp(err);

	if (abs(err) <= pid->deadband)
		return 0;

	pterm = mul_fp(pid->p_gain, fp_error);

	pid->integral += fp_error;

	/* limit the integral term */
	integral_limit = int_tofp(30);
	if (pid->integral > integral_limit)
		pid->integral = integral_limit;
	if (pid->integral < -integral_limit)
		pid->integral = -integral_limit;

	dterm = mul_fp(pid->d_gain, (err - pid->last_err));
	pid->last_err = err;

	result = pterm + mul_fp(pid->integral, pid->i_gain) + dterm;

	return (signed int)fp_toint(result);
}