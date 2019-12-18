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
struct b43_wldev {int /*<<< orphan*/  wl; } ;
struct b206x_init_tab_entry {int flags; int /*<<< orphan*/  value_a; int /*<<< orphan*/  offset; int /*<<< orphan*/  value_g; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct b206x_init_tab_entry*) ; 
 int B206X_FLAG_A ; 
 int B206X_FLAG_G ; 
 scalar_t__ IEEE80211_BAND_2GHZ ; 
 struct b206x_init_tab_entry* b2062_init_tab ; 
 scalar_t__ b43_current_band (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_radio_write (struct b43_wldev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void b2062_upload_init_table(struct b43_wldev *dev)
{
	const struct b206x_init_tab_entry *e;
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(b2062_init_tab); i++) {
		e = &b2062_init_tab[i];
		if (b43_current_band(dev->wl) == IEEE80211_BAND_2GHZ) {
			if (!(e->flags & B206X_FLAG_G))
				continue;
			b43_radio_write(dev, e->offset, e->value_g);
		} else {
			if (!(e->flags & B206X_FLAG_A))
				continue;
			b43_radio_write(dev, e->offset, e->value_a);
		}
	}
}