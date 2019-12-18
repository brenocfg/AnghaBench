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
struct _pid {int setpoint; int deadband; int last_err; int /*<<< orphan*/  integral; } ;

/* Variables and functions */
 int /*<<< orphan*/  int_tofp (int) ; 

__attribute__((used)) static inline void pid_reset(struct _pid *pid, int setpoint, int busy,
			int deadband, int integral) {
	pid->setpoint = setpoint;
	pid->deadband  = deadband;
	pid->integral  = int_tofp(integral);
	pid->last_err  = setpoint - busy;
}