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
typedef  int u16 ;
struct net_device {int /*<<< orphan*/  name; } ;
struct hostap_interface {TYPE_1__* local; } ;
struct TYPE_2__ {int /*<<< orphan*/  cmdlock; scalar_t__ no_pri; } ;
typedef  TYPE_1__ local_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_EXTRA2 ; 
 int ETIMEDOUT ; 
 int HFA384X_AUX_MAGIC0 ; 
 int HFA384X_AUX_MAGIC1 ; 
 int HFA384X_AUX_MAGIC2 ; 
 int HFA384X_AUX_PORT_DISABLE ; 
 int HFA384X_AUX_PORT_DISABLED ; 
 int HFA384X_AUX_PORT_ENABLE ; 
 int HFA384X_AUX_PORT_ENABLED ; 
 int HFA384X_AUX_PORT_MASK ; 
 int HFA384X_CMD_BUSY ; 
 int HFA384X_CMD_BUSY_TIMEOUT ; 
 int /*<<< orphan*/  HFA384X_CMD_OFF ; 
 int /*<<< orphan*/  HFA384X_CONTROL_OFF ; 
 int HFA384X_INW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HFA384X_OUTW (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HFA384X_PARAM0_OFF ; 
 int /*<<< orphan*/  HFA384X_PARAM1_OFF ; 
 int /*<<< orphan*/  HFA384X_PARAM2_OFF ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct hostap_interface* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int prism2_enable_aux_port(struct net_device *dev, int enable)
{
	u16 val, reg;
	int i, tries;
	unsigned long flags;
	struct hostap_interface *iface;
	local_info_t *local;

	iface = netdev_priv(dev);
	local = iface->local;

	if (local->no_pri) {
		if (enable) {
			PDEBUG(DEBUG_EXTRA2, "%s: no PRI f/w - assuming Aux "
			       "port is already enabled\n", dev->name);
		}
		return 0;
	}

	spin_lock_irqsave(&local->cmdlock, flags);

	/* wait until busy bit is clear */
	tries = HFA384X_CMD_BUSY_TIMEOUT;
	while (HFA384X_INW(HFA384X_CMD_OFF) & HFA384X_CMD_BUSY && tries > 0) {
		tries--;
		udelay(1);
	}
	if (tries == 0) {
		reg = HFA384X_INW(HFA384X_CMD_OFF);
		spin_unlock_irqrestore(&local->cmdlock, flags);
		printk("%s: prism2_enable_aux_port - timeout - reg=0x%04x\n",
		       dev->name, reg);
		return -ETIMEDOUT;
	}

	val = HFA384X_INW(HFA384X_CONTROL_OFF);

	if (enable) {
		HFA384X_OUTW(HFA384X_AUX_MAGIC0, HFA384X_PARAM0_OFF);
		HFA384X_OUTW(HFA384X_AUX_MAGIC1, HFA384X_PARAM1_OFF);
		HFA384X_OUTW(HFA384X_AUX_MAGIC2, HFA384X_PARAM2_OFF);

		if ((val & HFA384X_AUX_PORT_MASK) != HFA384X_AUX_PORT_DISABLED)
			printk("prism2_enable_aux_port: was not disabled!?\n");
		val &= ~HFA384X_AUX_PORT_MASK;
		val |= HFA384X_AUX_PORT_ENABLE;
	} else {
		HFA384X_OUTW(0, HFA384X_PARAM0_OFF);
		HFA384X_OUTW(0, HFA384X_PARAM1_OFF);
		HFA384X_OUTW(0, HFA384X_PARAM2_OFF);

		if ((val & HFA384X_AUX_PORT_MASK) != HFA384X_AUX_PORT_ENABLED)
			printk("prism2_enable_aux_port: was not enabled!?\n");
		val &= ~HFA384X_AUX_PORT_MASK;
		val |= HFA384X_AUX_PORT_DISABLE;
	}
	HFA384X_OUTW(val, HFA384X_CONTROL_OFF);

	udelay(5);

	i = 10000;
	while (i > 0) {
		val = HFA384X_INW(HFA384X_CONTROL_OFF);
		val &= HFA384X_AUX_PORT_MASK;

		if ((enable && val == HFA384X_AUX_PORT_ENABLED) ||
		    (!enable && val == HFA384X_AUX_PORT_DISABLED))
			break;

		udelay(10);
		i--;
	}

	spin_unlock_irqrestore(&local->cmdlock, flags);

	if (i == 0) {
		printk("prism2_enable_aux_port(%d) timed out\n",
		       enable);
		return -ETIMEDOUT;
	}

	return 0;
}