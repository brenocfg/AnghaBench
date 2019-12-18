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
struct ath5k_statistics {int /*<<< orphan*/  beacons; int /*<<< orphan*/  fcs_error; int /*<<< orphan*/  rts_ok; int /*<<< orphan*/  rts_fail; int /*<<< orphan*/  ack_fail; } ;
struct ath5k_hw {struct ath5k_statistics stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR5K_ACK_FAIL ; 
 int /*<<< orphan*/  AR5K_BEACON_CNT ; 
 int /*<<< orphan*/  AR5K_FCS_FAIL ; 
 int /*<<< orphan*/  AR5K_RTS_FAIL ; 
 int /*<<< orphan*/  AR5K_RTS_OK ; 
 scalar_t__ ath5k_hw_reg_read (struct ath5k_hw*,int /*<<< orphan*/ ) ; 

void
ath5k_hw_update_mib_counters(struct ath5k_hw *ah)
{
	struct ath5k_statistics *stats = &ah->stats;

	/* Read-And-Clear */
	stats->ack_fail += ath5k_hw_reg_read(ah, AR5K_ACK_FAIL);
	stats->rts_fail += ath5k_hw_reg_read(ah, AR5K_RTS_FAIL);
	stats->rts_ok += ath5k_hw_reg_read(ah, AR5K_RTS_OK);
	stats->fcs_error += ath5k_hw_reg_read(ah, AR5K_FCS_FAIL);
	stats->beacons += ath5k_hw_reg_read(ah, AR5K_BEACON_CNT);
}