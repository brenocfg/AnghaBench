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
typedef  scalar_t__ u16 ;
struct p54_rssi_db_entry {scalar_t__ const freq; } ;
struct p54_common {TYPE_1__* rssi_db; } ;
struct TYPE_2__ {int entries; scalar_t__ offset; scalar_t__ data; } ;

/* Variables and functions */
 scalar_t__ abs (scalar_t__ const) ; 
 struct p54_rssi_db_entry p54_rssi_default ; 
 int /*<<< orphan*/  same_band (scalar_t__ const,scalar_t__ const) ; 

struct p54_rssi_db_entry *p54_rssi_find(struct p54_common *priv, const u16 freq)
{
	struct p54_rssi_db_entry *entry;
	int i, found = -1;

	if (!priv->rssi_db)
		return &p54_rssi_default;

	entry = (void *)(priv->rssi_db->data + priv->rssi_db->offset);
	for (i = 0; i < priv->rssi_db->entries; i++) {
		if (!same_band(freq, entry[i].freq))
			continue;

		if (found == -1) {
			found = i;
			continue;
		}

		/* nearest match */
		if (abs(freq - entry[i].freq) <
		    abs(freq - entry[found].freq)) {
			found = i;
			continue;
		} else {
			break;
		}
	}

	return found < 0 ? &p54_rssi_default : &entry[found];
}