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
struct sh_tmu_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCNT ; 
 int /*<<< orphan*/  TCOR ; 
 int /*<<< orphan*/  TCR ; 
 int /*<<< orphan*/  sh_tmu_read (struct sh_tmu_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sh_tmu_start_stop_ch (struct sh_tmu_priv*,int) ; 
 int /*<<< orphan*/  sh_tmu_write (struct sh_tmu_priv*,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void sh_tmu_set_next(struct sh_tmu_priv *p, unsigned long delta,
			    int periodic)
{
	/* stop timer */
	sh_tmu_start_stop_ch(p, 0);

	/* acknowledge interrupt */
	sh_tmu_read(p, TCR);

	/* enable interrupt */
	sh_tmu_write(p, TCR, 0x0020);

	/* reload delta value in case of periodic timer */
	if (periodic)
		sh_tmu_write(p, TCOR, delta);
	else
		sh_tmu_write(p, TCOR, 0xffffffff);

	sh_tmu_write(p, TCNT, delta);

	/* start timer */
	sh_tmu_start_stop_ch(p, 1);
}