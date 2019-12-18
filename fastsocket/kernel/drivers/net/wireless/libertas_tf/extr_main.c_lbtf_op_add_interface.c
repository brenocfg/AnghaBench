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
typedef  int /*<<< orphan*/  u8 ;
struct lbtf_private {struct ieee80211_vif* vif; } ;
struct ieee80211_vif {int type; scalar_t__ addr; } ;
struct ieee80211_hw {struct lbtf_private* priv; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  LBTF_AP_MODE ; 
 int /*<<< orphan*/  LBTF_DEB_MACOPS ; 
 int /*<<< orphan*/  LBTF_STA_MODE ; 
#define  NL80211_IFTYPE_AP 130 
#define  NL80211_IFTYPE_MESH_POINT 129 
#define  NL80211_IFTYPE_STATION 128 
 int /*<<< orphan*/  lbtf_deb_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbtf_deb_leave (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbtf_set_mac_address (struct lbtf_private*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lbtf_set_mode (struct lbtf_private*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lbtf_op_add_interface(struct ieee80211_hw *hw,
			struct ieee80211_vif *vif)
{
	struct lbtf_private *priv = hw->priv;
	lbtf_deb_enter(LBTF_DEB_MACOPS);
	if (priv->vif != NULL)
		return -EOPNOTSUPP;

	priv->vif = vif;
	switch (vif->type) {
	case NL80211_IFTYPE_MESH_POINT:
	case NL80211_IFTYPE_AP:
		lbtf_set_mode(priv, LBTF_AP_MODE);
		break;
	case NL80211_IFTYPE_STATION:
		lbtf_set_mode(priv, LBTF_STA_MODE);
		break;
	default:
		priv->vif = NULL;
		return -EOPNOTSUPP;
	}
	lbtf_set_mac_address(priv, (u8 *) vif->addr);
	lbtf_deb_leave(LBTF_DEB_MACOPS);
	return 0;
}