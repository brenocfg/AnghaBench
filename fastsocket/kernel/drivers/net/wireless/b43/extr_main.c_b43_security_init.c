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
struct b43_wldev {int ktp; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_MMIO_RCMTA_COUNT ; 
 int /*<<< orphan*/  B43_NR_PAIRWISE_KEYS ; 
 int /*<<< orphan*/  B43_SHM_SHARED ; 
 int /*<<< orphan*/  B43_SHM_SH_KTP ; 
 int /*<<< orphan*/  b43_clear_keys (struct b43_wldev*) ; 
 int b43_shm_read16 (struct b43_wldev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_write16 (struct b43_wldev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void b43_security_init(struct b43_wldev *dev)
{
	dev->ktp = b43_shm_read16(dev, B43_SHM_SHARED, B43_SHM_SH_KTP);
	/* KTP is a word address, but we address SHM bytewise.
	 * So multiply by two.
	 */
	dev->ktp *= 2;
	/* Number of RCMTA address slots */
	b43_write16(dev, B43_MMIO_RCMTA_COUNT, B43_NR_PAIRWISE_KEYS);
	/* Clear the key memory. */
	b43_clear_keys(dev);
}