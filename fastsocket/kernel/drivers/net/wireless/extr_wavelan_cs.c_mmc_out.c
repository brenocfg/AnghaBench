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
typedef  int u_short ;
typedef  int /*<<< orphan*/  u_long ;
typedef  int /*<<< orphan*/  u_char ;

/* Variables and functions */
 int /*<<< orphan*/  HASR (int /*<<< orphan*/ ) ; 
 int HASR_MMI_BUSY ; 
 int /*<<< orphan*/  MMD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MMR (int /*<<< orphan*/ ) ; 
 int MMR_MMI_WR ; 
 int inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void
mmc_out(u_long		base,
	u_short		o,
	u_char		d)
{
  int count = 0;

  /* Wait for MMC to go idle */
  while((count++ < 100) && (inb(HASR(base)) & HASR_MMI_BUSY))
    udelay(10);

  outb((u_char)((o << 1) | MMR_MMI_WR), MMR(base));
  outb(d, MMD(base));
}