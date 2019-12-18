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
struct mib_mdomain {int /*<<< orphan*/  tx_powerlevel; int /*<<< orphan*/  channel_list; } ;
struct at76_priv {TYPE_1__* hw; int /*<<< orphan*/  udev; } ;
struct TYPE_2__ {int /*<<< orphan*/  wiphy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_MIB ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MIB_MDOMAIN ; 
 int /*<<< orphan*/  at76_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int at76_get_mib (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mib_mdomain*,int) ; 
 int /*<<< orphan*/  hex2str (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kfree (struct mib_mdomain*) ; 
 struct mib_mdomain* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wiphy_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  wiphy_name (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void at76_dump_mib_mdomain(struct at76_priv *priv)
{
	int ret;
	struct mib_mdomain *m = kmalloc(sizeof(struct mib_mdomain), GFP_KERNEL);

	if (!m)
		return;

	ret = at76_get_mib(priv->udev, MIB_MDOMAIN, m,
			   sizeof(struct mib_mdomain));
	if (ret < 0) {
		wiphy_err(priv->hw->wiphy,
			  "at76_get_mib (MDOMAIN) failed: %d\n", ret);
		goto exit;
	}

	at76_dbg(DBG_MIB, "%s: MIB MDOMAIN: channel_list %s",
		 wiphy_name(priv->hw->wiphy),
		 hex2str(m->channel_list, sizeof(m->channel_list)));

	at76_dbg(DBG_MIB, "%s: MIB MDOMAIN: tx_powerlevel %s",
		 wiphy_name(priv->hw->wiphy),
		 hex2str(m->tx_powerlevel, sizeof(m->tx_powerlevel)));
exit:
	kfree(m);
}