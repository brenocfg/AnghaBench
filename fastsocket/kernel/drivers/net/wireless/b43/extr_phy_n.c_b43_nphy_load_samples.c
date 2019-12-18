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
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_2__ {struct b43_phy_n* n; } ;
struct b43_wldev {int /*<<< orphan*/  wl; TYPE_1__ phy; } ;
struct b43_phy_n {scalar_t__ hang_avoid; } ;
struct b43_c32 {int i; int q; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_NTAB32 (int,int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  b43_nphy_stay_in_carrier_search (struct b43_wldev*,int) ; 
 int /*<<< orphan*/  b43_ntab_write_bulk (struct b43_wldev*,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  b43err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int b43_nphy_load_samples(struct b43_wldev *dev,
					struct b43_c32 *samples, u16 len) {
	struct b43_phy_n *nphy = dev->phy.n;
	u16 i;
	u32 *data;

	data = kzalloc(len * sizeof(u32), GFP_KERNEL);
	if (!data) {
		b43err(dev->wl, "allocation for samples loading failed\n");
		return -ENOMEM;
	}
	if (nphy->hang_avoid)
		b43_nphy_stay_in_carrier_search(dev, 1);

	for (i = 0; i < len; i++) {
		data[i] = (samples[i].i & 0x3FF << 10);
		data[i] |= samples[i].q & 0x3FF;
	}
	b43_ntab_write_bulk(dev, B43_NTAB32(17, 0), len, data);

	kfree(data);
	if (nphy->hang_avoid)
		b43_nphy_stay_in_carrier_search(dev, 0);
	return 0;
}