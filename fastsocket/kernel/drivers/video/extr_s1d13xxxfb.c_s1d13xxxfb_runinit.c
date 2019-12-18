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
struct s1d13xxxfb_regval {scalar_t__ addr; scalar_t__ value; } ;
struct s1d13xxxfb_par {int dummy; } ;

/* Variables and functions */
 scalar_t__ S1DREG_DELAYOFF ; 
 scalar_t__ S1DREG_DELAYON ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  s1d13xxxfb_writereg (struct s1d13xxxfb_par*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static inline void
s1d13xxxfb_runinit(struct s1d13xxxfb_par *par,
			const struct s1d13xxxfb_regval *initregs,
			const unsigned int size)
{
	int i;

	for (i = 0; i < size; i++) {
        	if ((initregs[i].addr == S1DREG_DELAYOFF) ||
				(initregs[i].addr == S1DREG_DELAYON))
			mdelay((int)initregs[i].value);
        	else {
			s1d13xxxfb_writereg(par, initregs[i].addr, initregs[i].value);
		}
        }

	/* make sure the hardware can cope with us */
	mdelay(1);
}