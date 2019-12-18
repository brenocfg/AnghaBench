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
typedef  void* u8 ;
struct ath_softc {int ant_rx; struct ath_hw* sc_ah; } ;
struct ath_hw_antcomb_conf {void* alt_lna_conf; void* main_lna_conf; } ;
struct ath_hw {int dummy; } ;
struct ath_common {scalar_t__ antenna_diversity; } ;

/* Variables and functions */
 void* ATH_ANT_DIV_COMB_LNA1 ; 
 void* ATH_ANT_DIV_COMB_LNA2 ; 
 int /*<<< orphan*/  ath9k_hw_antctrl_shared_chain_lnadiv (struct ath_hw*,int) ; 
 int /*<<< orphan*/  ath9k_hw_antdiv_comb_conf_get (struct ath_hw*,struct ath_hw_antcomb_conf*) ; 
 int /*<<< orphan*/  ath9k_hw_antdiv_comb_conf_set (struct ath_hw*,struct ath_hw_antcomb_conf*) ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 

void ath_ant_comb_update(struct ath_softc *sc)
{
	struct ath_hw *ah = sc->sc_ah;
	struct ath_common *common = ath9k_hw_common(ah);
	struct ath_hw_antcomb_conf div_ant_conf;
	u8 lna_conf;

	ath9k_hw_antdiv_comb_conf_get(ah, &div_ant_conf);

	if (sc->ant_rx == 1)
		lna_conf = ATH_ANT_DIV_COMB_LNA1;
	else
		lna_conf = ATH_ANT_DIV_COMB_LNA2;

	div_ant_conf.main_lna_conf = lna_conf;
	div_ant_conf.alt_lna_conf = lna_conf;

	ath9k_hw_antdiv_comb_conf_set(ah, &div_ant_conf);

	if (common->antenna_diversity)
		ath9k_hw_antctrl_shared_chain_lnadiv(ah, true);
}