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
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct b43_wldev {int /*<<< orphan*/  wl; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_DBG_KEYS ; 
 int B43_NR_GROUP_KEYS ; 
 int B43_NR_PAIRWISE_KEYS ; 
 int /*<<< orphan*/  B43_SHM_SHARED ; 
 int B43_SHM_SH_TKIPTSCTTAK ; 
 int /*<<< orphan*/  B43_WARN_ON (int) ; 
 scalar_t__ b43_debug (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 scalar_t__ b43_new_kidx_api (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_shm_write16 (struct b43_wldev*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  b43dbg (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  modparam_hwtkip ; 

__attribute__((used)) static void rx_tkip_phase1_write(struct b43_wldev *dev, u8 index, u32 iv32,
		u16 *phase1key)
{
	unsigned int i;
	u32 offset;
	u8 pairwise_keys_start = B43_NR_GROUP_KEYS * 2;

	if (!modparam_hwtkip)
		return;

	if (b43_new_kidx_api(dev))
		pairwise_keys_start = B43_NR_GROUP_KEYS;

	B43_WARN_ON(index < pairwise_keys_start);
	/* We have four default TX keys and possibly four default RX keys.
	 * Physical mac 0 is mapped to physical key 4 or 8, depending
	 * on the firmware version.
	 * So we must adjust the index here.
	 */
	index -= pairwise_keys_start;
	B43_WARN_ON(index >= B43_NR_PAIRWISE_KEYS);

	if (b43_debug(dev, B43_DBG_KEYS)) {
		b43dbg(dev->wl, "rx_tkip_phase1_write : idx 0x%x, iv32 0x%x\n",
				index, iv32);
	}
	/* Write the key to the  RX tkip shared mem */
	offset = B43_SHM_SH_TKIPTSCTTAK + index * (10 + 4);
	for (i = 0; i < 10; i += 2) {
		b43_shm_write16(dev, B43_SHM_SHARED, offset + i,
				phase1key ? phase1key[i / 2] : 0);
	}
	b43_shm_write16(dev, B43_SHM_SHARED, offset + i, iv32);
	b43_shm_write16(dev, B43_SHM_SHARED, offset + i + 2, iv32 >> 16);
}