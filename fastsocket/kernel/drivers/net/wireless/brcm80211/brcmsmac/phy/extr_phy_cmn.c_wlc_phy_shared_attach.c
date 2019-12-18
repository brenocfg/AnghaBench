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
struct shared_phy_params {int /*<<< orphan*/  boardflags2; int /*<<< orphan*/  boardflags; int /*<<< orphan*/  boardrev; int /*<<< orphan*/  boardtype; int /*<<< orphan*/  sromrev; int /*<<< orphan*/  chippkg; int /*<<< orphan*/  chiprev; int /*<<< orphan*/  chip; int /*<<< orphan*/  did; int /*<<< orphan*/  vid; int /*<<< orphan*/  corerev; int /*<<< orphan*/  unit; int /*<<< orphan*/  physhim; int /*<<< orphan*/  sih; } ;
struct shared_phy {int /*<<< orphan*/  rssi_mode; int /*<<< orphan*/  glacial_timer; int /*<<< orphan*/  slow_timer; int /*<<< orphan*/  fast_timer; int /*<<< orphan*/  boardflags2; int /*<<< orphan*/  boardflags; int /*<<< orphan*/  boardrev; int /*<<< orphan*/  boardtype; int /*<<< orphan*/  sromrev; int /*<<< orphan*/  chippkg; int /*<<< orphan*/  chiprev; int /*<<< orphan*/  chip; int /*<<< orphan*/  did; int /*<<< orphan*/  vid; int /*<<< orphan*/  corerev; int /*<<< orphan*/  unit; int /*<<< orphan*/  physhim; int /*<<< orphan*/  sih; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  PHY_SW_TIMER_FAST ; 
 int /*<<< orphan*/  PHY_SW_TIMER_GLACIAL ; 
 int /*<<< orphan*/  PHY_SW_TIMER_SLOW ; 
 int /*<<< orphan*/  RSSI_ANT_MERGE_MAX ; 
 struct shared_phy* kzalloc (int,int /*<<< orphan*/ ) ; 

struct shared_phy *wlc_phy_shared_attach(struct shared_phy_params *shp)
{
	struct shared_phy *sh;

	sh = kzalloc(sizeof(struct shared_phy), GFP_ATOMIC);
	if (sh == NULL)
		return NULL;

	sh->sih = shp->sih;
	sh->physhim = shp->physhim;
	sh->unit = shp->unit;
	sh->corerev = shp->corerev;

	sh->vid = shp->vid;
	sh->did = shp->did;
	sh->chip = shp->chip;
	sh->chiprev = shp->chiprev;
	sh->chippkg = shp->chippkg;
	sh->sromrev = shp->sromrev;
	sh->boardtype = shp->boardtype;
	sh->boardrev = shp->boardrev;
	sh->boardflags = shp->boardflags;
	sh->boardflags2 = shp->boardflags2;

	sh->fast_timer = PHY_SW_TIMER_FAST;
	sh->slow_timer = PHY_SW_TIMER_SLOW;
	sh->glacial_timer = PHY_SW_TIMER_GLACIAL;

	sh->rssi_mode = RSSI_ANT_MERGE_MAX;

	return sh;
}