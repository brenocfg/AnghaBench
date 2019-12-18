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
typedef  int /*<<< orphan*/  tsc_arr ;
struct hermes {TYPE_1__* ops; } ;
struct orinoco_private {struct hermes hw; } ;
struct TYPE_2__ {int (* read_ltv ) (struct hermes*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ***) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  HERMES_RID_CURRENT_TKIP_IV ; 
 int ORINOCO_SEQ_LEN ; 
 int /*<<< orphan*/  USER_BAP ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int stub1 (struct hermes*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ***) ; 

int orinoco_hw_get_tkip_iv(struct orinoco_private *priv, int key, u8 *tsc)
{
	struct hermes *hw = &priv->hw;
	int err = 0;
	u8 tsc_arr[4][ORINOCO_SEQ_LEN];

	if ((key < 0) || (key >= 4))
		return -EINVAL;

	err = hw->ops->read_ltv(hw, USER_BAP, HERMES_RID_CURRENT_TKIP_IV,
				sizeof(tsc_arr), NULL, &tsc_arr);
	if (!err)
		memcpy(tsc, &tsc_arr[key][0], sizeof(tsc_arr[0]));

	return err;
}