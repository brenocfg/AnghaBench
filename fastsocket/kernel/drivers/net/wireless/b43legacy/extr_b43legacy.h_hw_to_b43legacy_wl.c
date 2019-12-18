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
struct ieee80211_hw {struct b43legacy_wl* priv; } ;
struct b43legacy_wl {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline
struct b43legacy_wl *hw_to_b43legacy_wl(struct ieee80211_hw *hw)
{
	return hw->priv;
}