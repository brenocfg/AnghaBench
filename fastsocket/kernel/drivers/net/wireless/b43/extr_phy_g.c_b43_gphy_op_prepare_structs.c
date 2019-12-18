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
struct b43_phy {struct b43_phy_g* g; } ;
struct b43_wldev {struct b43_phy phy; } ;
struct b43_txpower_lo_control {int tx_bias; int /*<<< orphan*/  calib_list; } ;
struct b43_phy_g {void* tssi2dbm; int tgt_idle_tssi; int* nrssi; int* nrssi_lt; int lofcal; int initval; int average_tssi; int /*<<< orphan*/  ofdmtab_addr_direction; int /*<<< orphan*/  interfmode; struct b43_phy_g* minlowsig; struct b43_txpower_lo_control* lo_control; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int*) ; 
 int /*<<< orphan*/  B43_INTERFMODE_NONE ; 
 int /*<<< orphan*/  B43_OFDMTAB_DIRECTION_UNKNOWN ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct b43_phy_g*,int,int) ; 

__attribute__((used)) static void b43_gphy_op_prepare_structs(struct b43_wldev *dev)
{
	struct b43_phy *phy = &dev->phy;
	struct b43_phy_g *gphy = phy->g;
	const void *tssi2dbm;
	int tgt_idle_tssi;
	struct b43_txpower_lo_control *lo;
	unsigned int i;

	/* tssi2dbm table is constant, so it is initialized at alloc time.
	 * Save a copy of the pointer. */
	tssi2dbm = gphy->tssi2dbm;
	tgt_idle_tssi = gphy->tgt_idle_tssi;
	/* Save the LO pointer. */
	lo = gphy->lo_control;

	/* Zero out the whole PHY structure. */
	memset(gphy, 0, sizeof(*gphy));

	/* Restore pointers. */
	gphy->tssi2dbm = tssi2dbm;
	gphy->tgt_idle_tssi = tgt_idle_tssi;
	gphy->lo_control = lo;

	memset(gphy->minlowsig, 0xFF, sizeof(gphy->minlowsig));

	/* NRSSI */
	for (i = 0; i < ARRAY_SIZE(gphy->nrssi); i++)
		gphy->nrssi[i] = -1000;
	for (i = 0; i < ARRAY_SIZE(gphy->nrssi_lt); i++)
		gphy->nrssi_lt[i] = i;

	gphy->lofcal = 0xFFFF;
	gphy->initval = 0xFFFF;

	gphy->interfmode = B43_INTERFMODE_NONE;

	/* OFDM-table address caching. */
	gphy->ofdmtab_addr_direction = B43_OFDMTAB_DIRECTION_UNKNOWN;

	gphy->average_tssi = 0xFF;

	/* Local Osciallator structure */
	lo->tx_bias = 0xFF;
	INIT_LIST_HEAD(&lo->calib_list);
}