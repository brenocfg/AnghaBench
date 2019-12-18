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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct tkip_ctx {int /*<<< orphan*/  p1k; } ;
struct ieee80211_key_conf {int /*<<< orphan*/ * key; } ;

/* Variables and functions */
 size_t NL80211_TKIP_DATA_OFFSET_ENCR_KEY ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tkip_mixing_phase1 (int /*<<< orphan*/  const*,struct tkip_ctx*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

void ieee80211_get_tkip_rx_p1k(struct ieee80211_key_conf *keyconf,
                               const u8 *ta, u32 iv32, u16 *p1k)
{
	const u8 *tk = &keyconf->key[NL80211_TKIP_DATA_OFFSET_ENCR_KEY];
	struct tkip_ctx ctx;

	tkip_mixing_phase1(tk, &ctx, ta, iv32);
	memcpy(p1k, ctx.p1k, sizeof(ctx.p1k));
}