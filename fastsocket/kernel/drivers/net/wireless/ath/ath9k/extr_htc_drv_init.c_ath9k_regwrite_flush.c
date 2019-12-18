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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct register_write {int dummy; } ;
struct ath_hw {int dummy; } ;
struct ath_common {scalar_t__ priv; } ;
struct ath9k_htc_priv {TYPE_1__* wmi; } ;
typedef  int /*<<< orphan*/  rsp_status ;
struct TYPE_2__ {int multi_write_idx; int /*<<< orphan*/  multi_write_mutex; int /*<<< orphan*/  multi_write; int /*<<< orphan*/  mwrite_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  WMI ; 
 int /*<<< orphan*/  WMI_REG_WRITE_CMDID ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int ath9k_wmi_cmd (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void ath9k_regwrite_flush(void *hw_priv)
{
	struct ath_hw *ah = (struct ath_hw *) hw_priv;
	struct ath_common *common = ath9k_hw_common(ah);
	struct ath9k_htc_priv *priv = (struct ath9k_htc_priv *) common->priv;
	u32 rsp_status;
	int r;

	atomic_dec(&priv->wmi->mwrite_cnt);

	mutex_lock(&priv->wmi->multi_write_mutex);

	if (priv->wmi->multi_write_idx) {
		r = ath9k_wmi_cmd(priv->wmi, WMI_REG_WRITE_CMDID,
			  (u8 *) &priv->wmi->multi_write,
			  sizeof(struct register_write) * priv->wmi->multi_write_idx,
			  (u8 *) &rsp_status, sizeof(rsp_status),
			  100);
		if (unlikely(r)) {
			ath_dbg(common, WMI,
				"REGISTER WRITE FAILED, multi len: %d\n",
				priv->wmi->multi_write_idx);
		}
		priv->wmi->multi_write_idx = 0;
	}

	mutex_unlock(&priv->wmi->multi_write_mutex);
}