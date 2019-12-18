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
struct atmel_private {int BSS_list_entries; int current_BSS; scalar_t__ operating_mode; scalar_t__ SSID_size; TYPE_1__* BSSinfo; int /*<<< orphan*/  SSID; scalar_t__ wep_is_on; scalar_t__ connect_to_any_BSS; } ;
struct TYPE_2__ {scalar_t__ BSStype; int channel; int RSSI; scalar_t__ SSIDsize; int /*<<< orphan*/  SSID; scalar_t__ UsingWEP; } ;

/* Variables and functions */
 scalar_t__ atmel_validate_channel (struct atmel_private*,int) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int retrieve_bss(struct atmel_private *priv)
{
	int i;
	int max_rssi = -128;
	int max_index = -1;

	if (priv->BSS_list_entries == 0)
		return -1;

	if (priv->connect_to_any_BSS) {
		/* Select a BSS with the max-RSSI but of the same type and of
		   the same WEP mode and that it is not marked as 'bad' (i.e.
		   we had previously failed to connect to this BSS with the
		   settings that we currently use) */
		priv->current_BSS = 0;
		for (i = 0; i < priv->BSS_list_entries; i++) {
			if (priv->operating_mode == priv->BSSinfo[i].BSStype &&
			    ((!priv->wep_is_on && !priv->BSSinfo[i].UsingWEP) ||
			     (priv->wep_is_on && priv->BSSinfo[i].UsingWEP)) &&
			    !(priv->BSSinfo[i].channel & 0x80)) {
				max_rssi = priv->BSSinfo[i].RSSI;
				priv->current_BSS = max_index = i;
			}
		}
		return max_index;
	}

	for (i = 0; i < priv->BSS_list_entries; i++) {
		if (priv->SSID_size == priv->BSSinfo[i].SSIDsize &&
		    memcmp(priv->SSID, priv->BSSinfo[i].SSID, priv->SSID_size) == 0 &&
		    priv->operating_mode == priv->BSSinfo[i].BSStype &&
		    atmel_validate_channel(priv, priv->BSSinfo[i].channel) == 0) {
			if (priv->BSSinfo[i].RSSI >= max_rssi) {
				max_rssi = priv->BSSinfo[i].RSSI;
				max_index = i;
			}
		}
	}
	return max_index;
}