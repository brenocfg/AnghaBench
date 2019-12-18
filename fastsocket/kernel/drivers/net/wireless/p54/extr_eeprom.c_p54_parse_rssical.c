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
typedef  scalar_t__ u16 ;
struct pda_rssi_cal_ext_entry {int /*<<< orphan*/  add; int /*<<< orphan*/  mul; int /*<<< orphan*/  freq; } ;
struct pda_rssi_cal_entry {int /*<<< orphan*/  add; int /*<<< orphan*/  mul; } ;
struct p54_rssi_db_entry {void* add; void* mul; scalar_t__ freq; } ;
struct p54_common {TYPE_1__* rssi_db; } ;
struct ieee80211_hw {int /*<<< orphan*/  wiphy; struct p54_common* priv; } ;
typedef  void* s16 ;
typedef  scalar_t__ __le16 ;
struct TYPE_2__ {unsigned long offset; size_t entries; int entry_size; size_t len; scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUMP_PREFIX_NONE ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  IEEE80211_BAND_2GHZ 129 
#define  IEEE80211_BAND_5GHZ 128 
 scalar_t__ PDR_RSSI_LINEAR_APPROXIMATION ; 
 scalar_t__ PDR_RSSI_LINEAR_APPROXIMATION_EXTENDED ; 
 scalar_t__ cpu_to_le16 (int /*<<< orphan*/ ) ; 
 TYPE_1__* kzalloc (size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p54_compare_rssichan ; 
 int /*<<< orphan*/  print_hex_dump_bytes (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sort (struct p54_rssi_db_entry*,size_t,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wiphy_err (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int p54_parse_rssical(struct ieee80211_hw *dev,
			     u8 *data, int len, u16 type)
{
	struct p54_common *priv = dev->priv;
	struct p54_rssi_db_entry *entry;
	size_t db_len, entries;
	int offset = 0, i;

	if (type != PDR_RSSI_LINEAR_APPROXIMATION_EXTENDED) {
		entries = (type == PDR_RSSI_LINEAR_APPROXIMATION) ? 1 : 2;
		if (len != sizeof(struct pda_rssi_cal_entry) * entries) {
			wiphy_err(dev->wiphy, "rssical size mismatch.\n");
			goto err_data;
		}
	} else {
		/*
		 * Some devices (Dell 1450 USB, Xbow 5GHz card, etc...)
		 * have an empty two byte header.
		 */
		if (*((__le16 *)&data[offset]) == cpu_to_le16(0))
			offset += 2;

		entries = (len - offset) /
			sizeof(struct pda_rssi_cal_ext_entry);

		if (len < offset ||
		    (len - offset) % sizeof(struct pda_rssi_cal_ext_entry) ||
		    entries == 0) {
			wiphy_err(dev->wiphy, "invalid rssi database.\n");
			goto err_data;
		}
	}

	db_len = sizeof(*entry) * entries;
	priv->rssi_db = kzalloc(db_len + sizeof(*priv->rssi_db), GFP_KERNEL);
	if (!priv->rssi_db)
		return -ENOMEM;

	priv->rssi_db->offset = 0;
	priv->rssi_db->entries = entries;
	priv->rssi_db->entry_size = sizeof(*entry);
	priv->rssi_db->len = db_len;

	entry = (void *)((unsigned long)priv->rssi_db->data + priv->rssi_db->offset);
	if (type == PDR_RSSI_LINEAR_APPROXIMATION_EXTENDED) {
		struct pda_rssi_cal_ext_entry *cal = (void *) &data[offset];

		for (i = 0; i < entries; i++) {
			entry[i].freq = le16_to_cpu(cal[i].freq);
			entry[i].mul = (s16) le16_to_cpu(cal[i].mul);
			entry[i].add = (s16) le16_to_cpu(cal[i].add);
		}
	} else {
		struct pda_rssi_cal_entry *cal = (void *) &data[offset];

		for (i = 0; i < entries; i++) {
			u16 freq = 0;
			switch (i) {
			case IEEE80211_BAND_2GHZ:
				freq = 2437;
				break;
			case IEEE80211_BAND_5GHZ:
				freq = 5240;
				break;
			}

			entry[i].freq = freq;
			entry[i].mul = (s16) le16_to_cpu(cal[i].mul);
			entry[i].add = (s16) le16_to_cpu(cal[i].add);
		}
	}

	/* sort the list by channel frequency */
	sort(entry, entries, sizeof(*entry), p54_compare_rssichan, NULL);
	return 0;

err_data:
	wiphy_err(dev->wiphy,
		  "rssi calibration data packing type:(%x) len:%d.\n",
		  type, len);

	print_hex_dump_bytes("rssical:", DUMP_PREFIX_NONE, data, len);

	wiphy_err(dev->wiphy, "please report this issue.\n");
	return -EINVAL;
}