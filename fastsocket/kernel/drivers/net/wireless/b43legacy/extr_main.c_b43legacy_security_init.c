#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct b43legacy_wldev {int max_nr_keys; int ktp; TYPE_2__* dev; int /*<<< orphan*/  key; } ;
struct TYPE_3__ {int revision; } ;
struct TYPE_4__ {TYPE_1__ id; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  B43legacy_MMIO_RCMTA_COUNT ; 
 int /*<<< orphan*/  B43legacy_SHM_SHARED ; 
 int /*<<< orphan*/  B43legacy_WARN_ON (int) ; 
 int b43legacy_shm_read16 (struct b43legacy_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43legacy_write16 (struct b43legacy_wldev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void b43legacy_security_init(struct b43legacy_wldev *dev)
{
	dev->max_nr_keys = (dev->dev->id.revision >= 5) ? 58 : 20;
	B43legacy_WARN_ON(dev->max_nr_keys > ARRAY_SIZE(dev->key));
	dev->ktp = b43legacy_shm_read16(dev, B43legacy_SHM_SHARED,
					0x0056);
	/* KTP is a word address, but we address SHM bytewise.
	 * So multiply by two.
	 */
	dev->ktp *= 2;
	if (dev->dev->id.revision >= 5)
		/* Number of RCMTA address slots */
		b43legacy_write16(dev, B43legacy_MMIO_RCMTA_COUNT,
				  dev->max_nr_keys - 8);
}