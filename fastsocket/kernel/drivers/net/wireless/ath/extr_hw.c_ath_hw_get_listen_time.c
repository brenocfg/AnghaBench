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
struct ath_cycle_counters {int cycles; int rx_frame; int tx_frame; } ;
struct ath_common {int clockrate; struct ath_cycle_counters cc_ani; } ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct ath_cycle_counters*,int /*<<< orphan*/ ,int) ; 

int32_t ath_hw_get_listen_time(struct ath_common *common)
{
	struct ath_cycle_counters *cc = &common->cc_ani;
	int32_t listen_time;

	listen_time = (cc->cycles - cc->rx_frame - cc->tx_frame) /
		      (common->clockrate * 1000);

	memset(cc, 0, sizeof(*cc));

	return listen_time;
}