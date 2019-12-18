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
struct ath5k_ani_state {scalar_t__ listen_time; scalar_t__ cck_errors; scalar_t__ ofdm_errors; scalar_t__ last_listen; scalar_t__ last_cck_errors; scalar_t__ last_ofdm_errors; } ;

/* Variables and functions */

__attribute__((used)) static void
ath5k_ani_period_restart(struct ath5k_ani_state *as)
{
	/* keep last values for debugging */
	as->last_ofdm_errors = as->ofdm_errors;
	as->last_cck_errors = as->cck_errors;
	as->last_listen = as->listen_time;

	as->ofdm_errors = 0;
	as->cck_errors = 0;
	as->listen_time = 0;
}