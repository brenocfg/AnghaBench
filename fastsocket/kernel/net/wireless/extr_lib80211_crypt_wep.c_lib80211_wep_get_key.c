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
struct lib80211_wep_data {int key_len; int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int lib80211_wep_get_key(void *key, int len, u8 * seq, void *priv)
{
	struct lib80211_wep_data *wep = priv;

	if (len < wep->key_len)
		return -1;

	memcpy(key, wep->key, wep->key_len);

	return wep->key_len;
}