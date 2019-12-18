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
struct lib80211_tkip_data {unsigned long flags; } ;

/* Variables and functions */

__attribute__((used)) static unsigned long lib80211_tkip_set_flags(unsigned long flags, void *priv)
{
	struct lib80211_tkip_data *_priv = priv;
	unsigned long old_flags = _priv->flags;
	_priv->flags = flags;
	return old_flags;
}