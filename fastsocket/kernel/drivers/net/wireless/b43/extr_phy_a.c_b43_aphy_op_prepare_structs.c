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
struct b43_phy {struct b43_phy_a* a; } ;
struct b43_wldev {struct b43_phy phy; } ;
struct b43_phy_a {void* tssi2dbm; int tgt_idle_tssi; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct b43_phy_a*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void b43_aphy_op_prepare_structs(struct b43_wldev *dev)
{
	struct b43_phy *phy = &dev->phy;
	struct b43_phy_a *aphy = phy->a;
	const void *tssi2dbm;
	int tgt_idle_tssi;

	/* tssi2dbm table is constant, so it is initialized at alloc time.
	 * Save a copy of the pointer. */
	tssi2dbm = aphy->tssi2dbm;
	tgt_idle_tssi = aphy->tgt_idle_tssi;

	/* Zero out the whole PHY structure. */
	memset(aphy, 0, sizeof(*aphy));

	aphy->tssi2dbm = tssi2dbm;
	aphy->tgt_idle_tssi = tgt_idle_tssi;

	//TODO init struct b43_phy_a

}