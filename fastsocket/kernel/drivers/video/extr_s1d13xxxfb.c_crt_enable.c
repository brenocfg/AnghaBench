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
struct s1d13xxxfb_par {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  S1DREG_COM_DISP_MODE ; 
 int s1d13xxxfb_readreg (struct s1d13xxxfb_par*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s1d13xxxfb_writereg (struct s1d13xxxfb_par*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void
crt_enable(struct s1d13xxxfb_par *par, int enable)
{
	u8 mode = s1d13xxxfb_readreg(par, S1DREG_COM_DISP_MODE);

	if (enable)
		mode |= 0x02;
	else
		mode &= ~0x02;

	s1d13xxxfb_writereg(par, S1DREG_COM_DISP_MODE, mode);
}