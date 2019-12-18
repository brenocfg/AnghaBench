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
typedef  size_t u32 ;
struct emac_priv {scalar_t__* multicast_hash_cnt; size_t mac_hash1; size_t mac_hash2; } ;

/* Variables and functions */
 size_t BIT (size_t) ; 
 size_t hash_get (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hash_del(struct emac_priv *priv, u8 *mac_addr)
{
	u32 hash_value;
	u32 hash_bit;

	hash_value = hash_get(mac_addr);
	if (priv->multicast_hash_cnt[hash_value] > 0) {
		/* dec cntr for num of mcast addr's mapped to this hash bit */
		--priv->multicast_hash_cnt[hash_value];
	}

	/* if counter still > 0, at least one multicast address refers
	 * to this hash bit. so return 0 */
	if (priv->multicast_hash_cnt[hash_value] > 0)
		return 0;

	if (hash_value < 32) {
		hash_bit = BIT(hash_value);
		priv->mac_hash1 &= ~hash_bit;
	} else {
		hash_bit = BIT((hash_value - 32));
		priv->mac_hash2 &= ~hash_bit;
	}

	/* return 1 to indicate change in mac_hash registers reqd */
	return 1;
}