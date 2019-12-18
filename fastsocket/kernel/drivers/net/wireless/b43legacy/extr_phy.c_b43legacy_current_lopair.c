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
struct b43legacy_phy {int /*<<< orphan*/  txctl1; int /*<<< orphan*/  rfatt; int /*<<< orphan*/  bbatt; } ;
struct b43legacy_wldev {struct b43legacy_phy phy; } ;
struct b43legacy_lopair {int dummy; } ;

/* Variables and functions */
 struct b43legacy_lopair* b43legacy_find_lopair (struct b43legacy_wldev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline
struct b43legacy_lopair *b43legacy_current_lopair(struct b43legacy_wldev *dev)
{
	struct b43legacy_phy *phy = &dev->phy;

	return b43legacy_find_lopair(dev, phy->bbatt,
				     phy->rfatt, phy->txctl1);
}