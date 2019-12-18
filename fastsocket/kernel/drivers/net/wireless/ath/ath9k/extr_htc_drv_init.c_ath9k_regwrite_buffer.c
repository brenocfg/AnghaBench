#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct register_write {int dummy; } ;
struct ath_hw {int dummy; } ;
struct ath_common {scalar_t__ priv; } ;
struct ath9k_htc_priv {TYPE_2__* wmi; } ;
typedef  int /*<<< orphan*/  rsp_status ;
struct TYPE_4__ {size_t multi_write_idx; int /*<<< orphan*/  multi_write_mutex; TYPE_1__* multi_write; } ;
struct TYPE_3__ {void* val; void* reg; } ;

/* Variables and functions */
 size_t MAX_CMD_NUMBER ; 
 int /*<<< orphan*/  WMI ; 
 int /*<<< orphan*/  WMI_REG_WRITE_CMDID ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int ath9k_wmi_cmd (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*,int) ; 
 void* cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void ath9k_regwrite_buffer(void *hw_priv, u32 val, u32 reg_offset)
{
	struct ath_hw *ah = (struct ath_hw *) hw_priv;
	struct ath_common *common = ath9k_hw_common(ah);
	struct ath9k_htc_priv *priv = (struct ath9k_htc_priv *) common->priv;
	u32 rsp_status;
	int r;

	mutex_lock(&priv->wmi->multi_write_mutex);

	/* Store the register/value */
	priv->wmi->multi_write[priv->wmi->multi_write_idx].reg =
		cpu_to_be32(reg_offset);
	priv->wmi->multi_write[priv->wmi->multi_write_idx].val =
		cpu_to_be32(val);

	priv->wmi->multi_write_idx++;

	/* If the buffer is full, send it out. */
	if (priv->wmi->multi_write_idx == MAX_CMD_NUMBER) {
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