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
typedef  int u16 ;
struct dnet {int dummy; } ;

/* Variables and functions */
 int DNET_INTERNAL_WRITE ; 
 int /*<<< orphan*/  MACREG_ADDR ; 
 int /*<<< orphan*/  MACREG_DATA ; 
 int /*<<< orphan*/  dnet_writel (struct dnet*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ndelay (int) ; 

void dnet_writew_mac(struct dnet *bp, u16 reg, u16 val)
{
	/* load data to write */
	dnet_writel(bp, val, MACREG_DATA);

	/* issue a write */
	dnet_writel(bp, reg | DNET_INTERNAL_WRITE, MACREG_ADDR);

	/* since a read/write op to the MAC is very slow,
	 * we must wait before exiting */
	ndelay(500);
}