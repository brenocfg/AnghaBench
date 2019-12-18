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
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct wmi_cmd_hdr {int dummy; } ;
struct wmi {int last_cmd_id; int /*<<< orphan*/  op_mutex; int /*<<< orphan*/  cmd_wait; int /*<<< orphan*/  wmi_lock; scalar_t__ cmd_rsp_len; int /*<<< orphan*/ * cmd_rsp_buf; int /*<<< orphan*/  stopped; TYPE_1__* drv_priv; } ;
struct sk_buff {int dummy; } ;
struct htc_frame_hdr {int dummy; } ;
struct ath_hw {int ah_flags; } ;
struct ath_common {int dummy; } ;
typedef  enum wmi_cmd_id { ____Placeholder_wmi_cmd_id } wmi_cmd_id ;
struct TYPE_2__ {struct ath_hw* ah; } ;

/* Variables and functions */
 int AH_UNPLUGGED ; 
 int ENOMEM ; 
 int EPROTO ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  WMI ; 
 struct sk_buff* alloc_skb (scalar_t__,int /*<<< orphan*/ ) ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int ath9k_wmi_cmd_issue (struct wmi*,struct sk_buff*,int,scalar_t__) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ skb_put (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int wait_for_completion_timeout (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  wmi_cmd_to_name (int) ; 

int ath9k_wmi_cmd(struct wmi *wmi, enum wmi_cmd_id cmd_id,
		  u8 *cmd_buf, u32 cmd_len,
		  u8 *rsp_buf, u32 rsp_len,
		  u32 timeout)
{
	struct ath_hw *ah = wmi->drv_priv->ah;
	struct ath_common *common = ath9k_hw_common(ah);
	u16 headroom = sizeof(struct htc_frame_hdr) +
		       sizeof(struct wmi_cmd_hdr);
	struct sk_buff *skb;
	u8 *data;
	int time_left, ret = 0;
	unsigned long flags;

	if (ah->ah_flags & AH_UNPLUGGED)
		return 0;

	skb = alloc_skb(headroom + cmd_len, GFP_ATOMIC);
	if (!skb)
		return -ENOMEM;

	skb_reserve(skb, headroom);

	if (cmd_len != 0 && cmd_buf != NULL) {
		data = (u8 *) skb_put(skb, cmd_len);
		memcpy(data, cmd_buf, cmd_len);
	}

	mutex_lock(&wmi->op_mutex);

	/* check if wmi stopped flag is set */
	if (unlikely(wmi->stopped)) {
		ret = -EPROTO;
		goto out;
	}

	/* record the rsp buffer and length */
	wmi->cmd_rsp_buf = rsp_buf;
	wmi->cmd_rsp_len = rsp_len;

	spin_lock_irqsave(&wmi->wmi_lock, flags);
	wmi->last_cmd_id = cmd_id;
	spin_unlock_irqrestore(&wmi->wmi_lock, flags);

	ret = ath9k_wmi_cmd_issue(wmi, skb, cmd_id, cmd_len);
	if (ret)
		goto out;

	time_left = wait_for_completion_timeout(&wmi->cmd_wait, timeout);
	if (!time_left) {
		ath_dbg(common, WMI, "Timeout waiting for WMI command: %s\n",
			wmi_cmd_to_name(cmd_id));
		mutex_unlock(&wmi->op_mutex);
		return -ETIMEDOUT;
	}

	mutex_unlock(&wmi->op_mutex);

	return 0;

out:
	ath_dbg(common, WMI, "WMI failure for: %s\n", wmi_cmd_to_name(cmd_id));
	mutex_unlock(&wmi->op_mutex);
	kfree_skb(skb);

	return ret;
}