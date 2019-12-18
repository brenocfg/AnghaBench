#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct sk_buff {int dummy; } ;
struct TYPE_5__ {int magic2; int /*<<< orphan*/  magic; void* len; int /*<<< orphan*/  offset; } ;
struct TYPE_4__ {void* len; void* offset; } ;
struct p54_eeprom_lm86 {TYPE_2__ v2; TYPE_1__ v1; } ;
struct p54_common {int fw_var; int /*<<< orphan*/  eeprom_mutex; int /*<<< orphan*/ * eeprom; TYPE_3__* hw; int /*<<< orphan*/  eeprom_comp; } ;
struct TYPE_6__ {int /*<<< orphan*/  wiphy; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HZ ; 
 int /*<<< orphan*/  P54_CONTROL_TYPE_EEPROM_READBACK ; 
 int /*<<< orphan*/  P54_HDR_FLAG_CONTROL ; 
 void* cpu_to_le16 (scalar_t__) ; 
 int /*<<< orphan*/  cpu_to_le32 (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct sk_buff* p54_alloc_skb (struct p54_common*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p54_tx (struct p54_common*,struct sk_buff*) ; 
 scalar_t__ skb_put (struct sk_buff*,scalar_t__) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wait_for_completion_interruptible_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wiphy_err (int /*<<< orphan*/ ,char*) ; 

int p54_download_eeprom(struct p54_common *priv, void *buf,
			u16 offset, u16 len)
{
	struct p54_eeprom_lm86 *eeprom_hdr;
	struct sk_buff *skb;
	size_t eeprom_hdr_size;
	int ret = 0;

	if (priv->fw_var >= 0x509)
		eeprom_hdr_size = sizeof(*eeprom_hdr);
	else
		eeprom_hdr_size = 0x4;

	skb = p54_alloc_skb(priv, P54_HDR_FLAG_CONTROL, eeprom_hdr_size +
			    len, P54_CONTROL_TYPE_EEPROM_READBACK,
			    GFP_KERNEL);
	if (unlikely(!skb))
		return -ENOMEM;

	mutex_lock(&priv->eeprom_mutex);
	priv->eeprom = buf;
	eeprom_hdr = (struct p54_eeprom_lm86 *) skb_put(skb,
		eeprom_hdr_size + len);

	if (priv->fw_var < 0x509) {
		eeprom_hdr->v1.offset = cpu_to_le16(offset);
		eeprom_hdr->v1.len = cpu_to_le16(len);
	} else {
		eeprom_hdr->v2.offset = cpu_to_le32(offset);
		eeprom_hdr->v2.len = cpu_to_le16(len);
		eeprom_hdr->v2.magic2 = 0xf;
		memcpy(eeprom_hdr->v2.magic, (const char *)"LOCK", 4);
	}

	p54_tx(priv, skb);

	if (!wait_for_completion_interruptible_timeout(
	     &priv->eeprom_comp, HZ)) {
		wiphy_err(priv->hw->wiphy, "device does not respond!\n");
		ret = -EBUSY;
	}
	priv->eeprom = NULL;
	mutex_unlock(&priv->eeprom_mutex);
	return ret;
}