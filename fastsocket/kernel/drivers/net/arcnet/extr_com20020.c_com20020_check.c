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
struct net_device {int base_addr; } ;
struct arcnet_local {int setup; int clockm; int clockp; int setup2; int config; int timeout; int backplane; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACOMMAND (int) ; 
 int /*<<< orphan*/  ARCRESET0 ; 
 int ASTATUS () ; 
 int AUTOINCflag ; 
 int /*<<< orphan*/  BUGMSG (int /*<<< orphan*/ ,char*,int) ; 
 int BUS_ALIGN ; 
 int CFLAGScmd ; 
 int CONFIGclear ; 
 int /*<<< orphan*/  D_INIT_REASONS ; 
 int /*<<< orphan*/  D_NORMAL ; 
 int ENODEV ; 
 int NORXflag ; 
 int P1MODE ; 
 int RDDATAflag ; 
 int RESETclear ; 
 int RESETflag ; 
 int RESETtime ; 
 int /*<<< orphan*/  SETCONF ; 
 int /*<<< orphan*/  SET_SUBADR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SUB_SETUP1 ; 
 int /*<<< orphan*/  SUB_SETUP2 ; 
 int TESTvalue ; 
 int TXFREEflag ; 
 int _ADDR_HI ; 
 int _ADDR_LO ; 
 int _COMMAND ; 
 int _CONFIG ; 
 int _MEMDATA ; 
 int _XREG ; 
 int inb (int) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 struct arcnet_local* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  outb (int,int) ; 

int com20020_check(struct net_device *dev)
{
	int ioaddr = dev->base_addr, status;
	struct arcnet_local *lp = netdev_priv(dev);

	ARCRESET0;
	mdelay(RESETtime);

	lp->setup = lp->clockm ? 0 : (lp->clockp << 1);
	lp->setup2 = (lp->clockm << 4) | 8;

	/* CHECK: should we do this for SOHARD cards ? */
	/* Enable P1Mode for backplane mode */
	lp->setup = lp->setup | P1MODE;

	SET_SUBADR(SUB_SETUP1);
	outb(lp->setup, _XREG);

	if (lp->clockm != 0)
	{
		SET_SUBADR(SUB_SETUP2);
		outb(lp->setup2, _XREG);
	
		/* must now write the magic "restart operation" command */
		mdelay(1);
		outb(0x18, _COMMAND);
	}

	lp->config = 0x21 | (lp->timeout << 3) | (lp->backplane << 2);
	/* set node ID to 0x42 (but transmitter is disabled, so it's okay) */
	SETCONF;
	outb(0x42, ioaddr + BUS_ALIGN*7);

	status = ASTATUS();

	if ((status & 0x99) != (NORXflag | TXFREEflag | RESETflag)) {
		BUGMSG(D_NORMAL, "status invalid (%Xh).\n", status);
		return -ENODEV;
	}
	BUGMSG(D_INIT_REASONS, "status after reset: %X\n", status);

	/* Enable TX */
	outb(0x39, _CONFIG);
	outb(inb(ioaddr + BUS_ALIGN*8), ioaddr + BUS_ALIGN*7);

	ACOMMAND(CFLAGScmd | RESETclear | CONFIGclear);

	status = ASTATUS();
	BUGMSG(D_INIT_REASONS, "status after reset acknowledged: %X\n",
	       status);

	/* Read first location of memory */
	outb(0 | RDDATAflag | AUTOINCflag, _ADDR_HI);
	outb(0, _ADDR_LO);

	if ((status = inb(_MEMDATA)) != TESTvalue) {
		BUGMSG(D_NORMAL, "Signature byte not found (%02Xh != D1h).\n",
		       status);
		return -ENODEV;
	}
	return 0;
}