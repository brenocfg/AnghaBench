#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct b44 {int flags; TYPE_1__* dev; } ;
struct TYPE_2__ {int* dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  B44_ADDR_HI ; 
 int /*<<< orphan*/  B44_ADDR_LO ; 
 int /*<<< orphan*/  B44_DEVCTRL ; 
 int B44_FLAG_B0_ANDLATER ; 
 int /*<<< orphan*/  B44_RXCONFIG ; 
 int /*<<< orphan*/  B44_WKUP_LEN ; 
 int DEVCTRL_MPM ; 
 int DEVCTRL_PFE ; 
 int RXCONFIG_ALLMULTI ; 
 int WKUP_LEN_DISABLE ; 
 int /*<<< orphan*/  b44_setup_pseudo_magicp (struct b44*) ; 
 int /*<<< orphan*/  b44_setup_wol_pci (struct b44*) ; 
 int br32 (struct b44*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bw32 (struct b44*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void b44_setup_wol(struct b44 *bp)
{
	u32 val;

	bw32(bp, B44_RXCONFIG, RXCONFIG_ALLMULTI);

	if (bp->flags & B44_FLAG_B0_ANDLATER) {

		bw32(bp, B44_WKUP_LEN, WKUP_LEN_DISABLE);

		val = bp->dev->dev_addr[2] << 24 |
			bp->dev->dev_addr[3] << 16 |
			bp->dev->dev_addr[4] << 8 |
			bp->dev->dev_addr[5];
		bw32(bp, B44_ADDR_LO, val);

		val = bp->dev->dev_addr[0] << 8 |
			bp->dev->dev_addr[1];
		bw32(bp, B44_ADDR_HI, val);

		val = br32(bp, B44_DEVCTRL);
		bw32(bp, B44_DEVCTRL, val | DEVCTRL_MPM | DEVCTRL_PFE);

 	} else {
 		b44_setup_pseudo_magicp(bp);
 	}
	b44_setup_wol_pci(bp);
}