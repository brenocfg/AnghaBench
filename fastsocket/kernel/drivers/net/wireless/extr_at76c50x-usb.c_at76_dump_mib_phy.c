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
struct mib_phy {int /*<<< orphan*/  current_reg_domain; int /*<<< orphan*/  phy_type; int /*<<< orphan*/  current_cca_mode; int /*<<< orphan*/  channel_id; int /*<<< orphan*/ * operation_rate_set; int /*<<< orphan*/  cca_mode_supported; int /*<<< orphan*/  mpdu_max_length; int /*<<< orphan*/  plcp_header_length; int /*<<< orphan*/  preamble_length; int /*<<< orphan*/  sifs_time; int /*<<< orphan*/  slot_time; int /*<<< orphan*/  ed_threshold; } ;
struct at76_priv {TYPE_1__* hw; int /*<<< orphan*/  udev; } ;
struct TYPE_2__ {int /*<<< orphan*/  wiphy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_MIB ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MIB_PHY ; 
 int /*<<< orphan*/  at76_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int at76_get_mib (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mib_phy*,int) ; 
 int /*<<< orphan*/  kfree (struct mib_phy*) ; 
 struct mib_phy* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wiphy_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  wiphy_name (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void at76_dump_mib_phy(struct at76_priv *priv)
{
	int ret;
	struct mib_phy *m = kmalloc(sizeof(struct mib_phy), GFP_KERNEL);

	if (!m)
		return;

	ret = at76_get_mib(priv->udev, MIB_PHY, m, sizeof(struct mib_phy));
	if (ret < 0) {
		wiphy_err(priv->hw->wiphy,
			  "at76_get_mib (PHY) failed: %d\n", ret);
		goto exit;
	}

	at76_dbg(DBG_MIB, "%s: MIB PHY: ed_threshold %d slot_time %d "
		 "sifs_time %d preamble_length %d plcp_header_length %d "
		 "mpdu_max_length %d cca_mode_supported %d operation_rate_set "
		 "0x%x 0x%x 0x%x 0x%x channel_id %d current_cca_mode %d "
		 "phy_type %d current_reg_domain %d",
		 wiphy_name(priv->hw->wiphy), le32_to_cpu(m->ed_threshold),
		 le16_to_cpu(m->slot_time), le16_to_cpu(m->sifs_time),
		 le16_to_cpu(m->preamble_length),
		 le16_to_cpu(m->plcp_header_length),
		 le16_to_cpu(m->mpdu_max_length),
		 le16_to_cpu(m->cca_mode_supported), m->operation_rate_set[0],
		 m->operation_rate_set[1], m->operation_rate_set[2],
		 m->operation_rate_set[3], m->channel_id, m->current_cca_mode,
		 m->phy_type, m->current_reg_domain);
exit:
	kfree(m);
}