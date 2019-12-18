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
struct ath_ant_comb {int total_pkt_count; int main_total_rssi; int alt_total_rssi; int alt_recv_cnt; int scan; int alt_good; scalar_t__ count; int scan_not_start; int rssi_lna2; int rssi_lna1; int rssi_add; int rssi_sub; scalar_t__ main_recv_cnt; scalar_t__ scan_start_time; int /*<<< orphan*/  quick_scan_cnt; } ;
struct ath_softc {int /*<<< orphan*/  sc_ah; struct ath_ant_comb ant_comb; } ;
struct ath_rx_status {int rs_rssi_ctl0; int rs_rssi_ctl1; int rs_rssi_ctl2; scalar_t__ rs_moreaggr; } ;
struct ath_hw_antcomb_conf {int alt_lna_conf; int main_lna_conf; int lna1_lna2_delta; int /*<<< orphan*/  div_group; } ;

/* Variables and functions */
 int ATH_ANT_DIV_COMB_ALT_ANT_RATIO ; 
#define  ATH_ANT_DIV_COMB_LNA1 131 
 int ATH_ANT_DIV_COMB_LNA1_LNA2_SWITCH_DELTA ; 
#define  ATH_ANT_DIV_COMB_LNA1_MINUS_LNA2 130 
#define  ATH_ANT_DIV_COMB_LNA1_PLUS_LNA2 129 
#define  ATH_ANT_DIV_COMB_LNA2 128 
 scalar_t__ ATH_ANT_DIV_COMB_MAX_COUNT ; 
 int ATH_ANT_DIV_COMB_MAX_PKTCOUNT ; 
 int /*<<< orphan*/  ATH_ANT_DIV_COMB_SHORT_SCAN_INTR ; 
 int ATH_ANT_DIV_COMB_SHORT_SCAN_PKTCOUNT ; 
 int ATH_ANT_RX_CURRENT_SHIFT ; 
 int ATH_ANT_RX_MAIN_SHIFT ; 
 int ATH_ANT_RX_MASK ; 
 int /*<<< orphan*/  ath9k_hw_antdiv_comb_conf_get (int /*<<< orphan*/ ,struct ath_hw_antcomb_conf*) ; 
 int /*<<< orphan*/  ath9k_hw_antdiv_comb_conf_set (int /*<<< orphan*/ ,struct ath_hw_antcomb_conf*) ; 
 scalar_t__ ath_ant_div_comb_alt_check (int /*<<< orphan*/ ,int,int,int,int,int) ; 
 int /*<<< orphan*/  ath_ant_div_conf_fast_divbias (struct ath_hw_antcomb_conf*,struct ath_ant_comb*,int) ; 
 int /*<<< orphan*/  ath_lnaconf_alt_good_scan (struct ath_ant_comb*,struct ath_hw_antcomb_conf,int) ; 
 int /*<<< orphan*/  ath_select_ant_div_from_quick_scan (struct ath_ant_comb*,struct ath_hw_antcomb_conf*,int,int,int) ; 
 scalar_t__ jiffies ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 

void ath_ant_comb_scan(struct ath_softc *sc, struct ath_rx_status *rs)
{
	struct ath_hw_antcomb_conf div_ant_conf;
	struct ath_ant_comb *antcomb = &sc->ant_comb;
	int alt_ratio = 0, alt_rssi_avg = 0, main_rssi_avg = 0, curr_alt_set;
	int curr_main_set;
	int main_rssi = rs->rs_rssi_ctl0;
	int alt_rssi = rs->rs_rssi_ctl1;
	int rx_ant_conf,  main_ant_conf;
	bool short_scan = false;

	rx_ant_conf = (rs->rs_rssi_ctl2 >> ATH_ANT_RX_CURRENT_SHIFT) &
		       ATH_ANT_RX_MASK;
	main_ant_conf = (rs->rs_rssi_ctl2 >> ATH_ANT_RX_MAIN_SHIFT) &
			 ATH_ANT_RX_MASK;

	/* Record packet only when both main_rssi and  alt_rssi is positive */
	if (main_rssi > 0 && alt_rssi > 0) {
		antcomb->total_pkt_count++;
		antcomb->main_total_rssi += main_rssi;
		antcomb->alt_total_rssi  += alt_rssi;
		if (main_ant_conf == rx_ant_conf)
			antcomb->main_recv_cnt++;
		else
			antcomb->alt_recv_cnt++;
	}

	/* Short scan check */
	if (antcomb->scan && antcomb->alt_good) {
		if (time_after(jiffies, antcomb->scan_start_time +
		    msecs_to_jiffies(ATH_ANT_DIV_COMB_SHORT_SCAN_INTR)))
			short_scan = true;
		else
			if (antcomb->total_pkt_count ==
			    ATH_ANT_DIV_COMB_SHORT_SCAN_PKTCOUNT) {
				alt_ratio = ((antcomb->alt_recv_cnt * 100) /
					    antcomb->total_pkt_count);
				if (alt_ratio < ATH_ANT_DIV_COMB_ALT_ANT_RATIO)
					short_scan = true;
			}
	}

	if (((antcomb->total_pkt_count < ATH_ANT_DIV_COMB_MAX_PKTCOUNT) ||
	    rs->rs_moreaggr) && !short_scan)
		return;

	if (antcomb->total_pkt_count) {
		alt_ratio = ((antcomb->alt_recv_cnt * 100) /
			     antcomb->total_pkt_count);
		main_rssi_avg = (antcomb->main_total_rssi /
				 antcomb->total_pkt_count);
		alt_rssi_avg = (antcomb->alt_total_rssi /
				 antcomb->total_pkt_count);
	}


	ath9k_hw_antdiv_comb_conf_get(sc->sc_ah, &div_ant_conf);
	curr_alt_set = div_ant_conf.alt_lna_conf;
	curr_main_set = div_ant_conf.main_lna_conf;

	antcomb->count++;

	if (antcomb->count == ATH_ANT_DIV_COMB_MAX_COUNT) {
		if (alt_ratio > ATH_ANT_DIV_COMB_ALT_ANT_RATIO) {
			ath_lnaconf_alt_good_scan(antcomb, div_ant_conf,
						  main_rssi_avg);
			antcomb->alt_good = true;
		} else {
			antcomb->alt_good = false;
		}

		antcomb->count = 0;
		antcomb->scan = true;
		antcomb->scan_not_start = true;
	}

	if (!antcomb->scan) {
		if (ath_ant_div_comb_alt_check(div_ant_conf.div_group,
					alt_ratio, curr_main_set, curr_alt_set,
					alt_rssi_avg, main_rssi_avg)) {
			if (curr_alt_set == ATH_ANT_DIV_COMB_LNA2) {
				/* Switch main and alt LNA */
				div_ant_conf.main_lna_conf =
						ATH_ANT_DIV_COMB_LNA2;
				div_ant_conf.alt_lna_conf  =
						ATH_ANT_DIV_COMB_LNA1;
			} else if (curr_alt_set == ATH_ANT_DIV_COMB_LNA1) {
				div_ant_conf.main_lna_conf =
						ATH_ANT_DIV_COMB_LNA1;
				div_ant_conf.alt_lna_conf  =
						ATH_ANT_DIV_COMB_LNA2;
			}

			goto div_comb_done;
		} else if ((curr_alt_set != ATH_ANT_DIV_COMB_LNA1) &&
			   (curr_alt_set != ATH_ANT_DIV_COMB_LNA2)) {
			/* Set alt to another LNA */
			if (curr_main_set == ATH_ANT_DIV_COMB_LNA2)
				div_ant_conf.alt_lna_conf =
						ATH_ANT_DIV_COMB_LNA1;
			else if (curr_main_set == ATH_ANT_DIV_COMB_LNA1)
				div_ant_conf.alt_lna_conf =
						ATH_ANT_DIV_COMB_LNA2;

			goto div_comb_done;
		}

		if ((alt_rssi_avg < (main_rssi_avg +
				     div_ant_conf.lna1_lna2_delta)))
			goto div_comb_done;
	}

	if (!antcomb->scan_not_start) {
		switch (curr_alt_set) {
		case ATH_ANT_DIV_COMB_LNA2:
			antcomb->rssi_lna2 = alt_rssi_avg;
			antcomb->rssi_lna1 = main_rssi_avg;
			antcomb->scan = true;
			/* set to A+B */
			div_ant_conf.main_lna_conf =
				ATH_ANT_DIV_COMB_LNA1;
			div_ant_conf.alt_lna_conf  =
				ATH_ANT_DIV_COMB_LNA1_PLUS_LNA2;
			break;
		case ATH_ANT_DIV_COMB_LNA1:
			antcomb->rssi_lna1 = alt_rssi_avg;
			antcomb->rssi_lna2 = main_rssi_avg;
			antcomb->scan = true;
			/* set to A+B */
			div_ant_conf.main_lna_conf = ATH_ANT_DIV_COMB_LNA2;
			div_ant_conf.alt_lna_conf  =
				ATH_ANT_DIV_COMB_LNA1_PLUS_LNA2;
			break;
		case ATH_ANT_DIV_COMB_LNA1_PLUS_LNA2:
			antcomb->rssi_add = alt_rssi_avg;
			antcomb->scan = true;
			/* set to A-B */
			div_ant_conf.alt_lna_conf =
				ATH_ANT_DIV_COMB_LNA1_MINUS_LNA2;
			break;
		case ATH_ANT_DIV_COMB_LNA1_MINUS_LNA2:
			antcomb->rssi_sub = alt_rssi_avg;
			antcomb->scan = false;
			if (antcomb->rssi_lna2 >
			    (antcomb->rssi_lna1 +
			    ATH_ANT_DIV_COMB_LNA1_LNA2_SWITCH_DELTA)) {
				/* use LNA2 as main LNA */
				if ((antcomb->rssi_add > antcomb->rssi_lna1) &&
				    (antcomb->rssi_add > antcomb->rssi_sub)) {
					/* set to A+B */
					div_ant_conf.main_lna_conf =
						ATH_ANT_DIV_COMB_LNA2;
					div_ant_conf.alt_lna_conf  =
						ATH_ANT_DIV_COMB_LNA1_PLUS_LNA2;
				} else if (antcomb->rssi_sub >
					   antcomb->rssi_lna1) {
					/* set to A-B */
					div_ant_conf.main_lna_conf =
						ATH_ANT_DIV_COMB_LNA2;
					div_ant_conf.alt_lna_conf =
						ATH_ANT_DIV_COMB_LNA1_MINUS_LNA2;
				} else {
					/* set to LNA1 */
					div_ant_conf.main_lna_conf =
						ATH_ANT_DIV_COMB_LNA2;
					div_ant_conf.alt_lna_conf =
						ATH_ANT_DIV_COMB_LNA1;
				}
			} else {
				/* use LNA1 as main LNA */
				if ((antcomb->rssi_add > antcomb->rssi_lna2) &&
				    (antcomb->rssi_add > antcomb->rssi_sub)) {
					/* set to A+B */
					div_ant_conf.main_lna_conf =
						ATH_ANT_DIV_COMB_LNA1;
					div_ant_conf.alt_lna_conf  =
						ATH_ANT_DIV_COMB_LNA1_PLUS_LNA2;
				} else if (antcomb->rssi_sub >
					   antcomb->rssi_lna1) {
					/* set to A-B */
					div_ant_conf.main_lna_conf =
						ATH_ANT_DIV_COMB_LNA1;
					div_ant_conf.alt_lna_conf =
						ATH_ANT_DIV_COMB_LNA1_MINUS_LNA2;
				} else {
					/* set to LNA2 */
					div_ant_conf.main_lna_conf =
						ATH_ANT_DIV_COMB_LNA1;
					div_ant_conf.alt_lna_conf =
						ATH_ANT_DIV_COMB_LNA2;
				}
			}
			break;
		default:
			break;
		}
	} else {
		if (!antcomb->alt_good) {
			antcomb->scan_not_start = false;
			/* Set alt to another LNA */
			if (curr_main_set == ATH_ANT_DIV_COMB_LNA2) {
				div_ant_conf.main_lna_conf =
						ATH_ANT_DIV_COMB_LNA2;
				div_ant_conf.alt_lna_conf =
						ATH_ANT_DIV_COMB_LNA1;
			} else if (curr_main_set == ATH_ANT_DIV_COMB_LNA1) {
				div_ant_conf.main_lna_conf =
						ATH_ANT_DIV_COMB_LNA1;
				div_ant_conf.alt_lna_conf =
						ATH_ANT_DIV_COMB_LNA2;
			}
			goto div_comb_done;
		}
	}

	ath_select_ant_div_from_quick_scan(antcomb, &div_ant_conf,
					   main_rssi_avg, alt_rssi_avg,
					   alt_ratio);

	antcomb->quick_scan_cnt++;

div_comb_done:
	ath_ant_div_conf_fast_divbias(&div_ant_conf, antcomb, alt_ratio);
	ath9k_hw_antdiv_comb_conf_set(sc->sc_ah, &div_ant_conf);

	antcomb->scan_start_time = jiffies;
	antcomb->total_pkt_count = 0;
	antcomb->main_total_rssi = 0;
	antcomb->alt_total_rssi = 0;
	antcomb->main_recv_cnt = 0;
	antcomb->alt_recv_cnt = 0;
}