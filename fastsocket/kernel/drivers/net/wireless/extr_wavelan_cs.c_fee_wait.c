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
typedef  int /*<<< orphan*/  u_long ;

/* Variables and functions */
 int MMR_FEE_STATUS_BUSY ; 
 int mmc_in (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmr_fee_status ; 
 int /*<<< orphan*/  mmroff (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void
fee_wait(u_long		base,	/* i/o port of the card */
	 int		delay,	/* Base delay to wait for */
	 int		number)	/* Number of time to wait */
{
  int		count = 0;	/* Wait only a limited time */

  while((count++ < number) &&
	(mmc_in(base, mmroff(0, mmr_fee_status)) & MMR_FEE_STATUS_BUSY))
    udelay(delay);
}