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
struct ath_mci_profile {int dummy; } ;
struct ath_btcoex {struct ath_mci_profile mci; } ;
struct ath_softc {struct ath_btcoex btcoex; int /*<<< orphan*/  sc_ah; } ;
struct ath_mci_profile_info {scalar_t__ type; scalar_t__ start; } ;
struct ath_common {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEC_PROF (struct ath_mci_profile*,struct ath_mci_profile_info*) ; 
 int /*<<< orphan*/  INC_PROF (struct ath_mci_profile*,struct ath_mci_profile_info*) ; 
 struct ath_common* ath9k_hw_common (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath_mci_add_profile (struct ath_common*,struct ath_mci_profile*,struct ath_mci_profile_info*) ; 
 int /*<<< orphan*/  ath_mci_del_profile (struct ath_common*,struct ath_mci_profile*,struct ath_mci_profile_info*) ; 
 struct ath_mci_profile_info* ath_mci_find_profile (struct ath_mci_profile*,struct ath_mci_profile_info*) ; 
 int /*<<< orphan*/  ath_mci_set_concur_txprio (struct ath_softc*) ; 
 int /*<<< orphan*/  memcpy (struct ath_mci_profile_info*,struct ath_mci_profile_info*,int) ; 

__attribute__((used)) static u8 ath_mci_process_profile(struct ath_softc *sc,
				  struct ath_mci_profile_info *info)
{
	struct ath_common *common = ath9k_hw_common(sc->sc_ah);
	struct ath_btcoex *btcoex = &sc->btcoex;
	struct ath_mci_profile *mci = &btcoex->mci;
	struct ath_mci_profile_info *entry = NULL;

	entry = ath_mci_find_profile(mci, info);
	if (entry) {
		/*
		 * Two MCI interrupts are generated while connecting to
		 * headset and A2DP profile, but only one MCI interrupt
		 * is generated with last added profile type while disconnecting
		 * both profiles.
		 * So while adding second profile type decrement
		 * the first one.
		 */
		if (entry->type != info->type) {
			DEC_PROF(mci, entry);
			INC_PROF(mci, info);
		}
		memcpy(entry, info, 10);
	}

	if (info->start) {
		if (!entry && !ath_mci_add_profile(common, mci, info))
			return 0;
	} else
		ath_mci_del_profile(common, mci, entry);

	ath_mci_set_concur_txprio(sc);
	return 1;
}