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
struct sbmac_softc {int sbm_state; } ;
typedef  enum sbmac_state { ____Placeholder_sbmac_state } sbmac_state ;

/* Variables and functions */
 int /*<<< orphan*/  sbmac_channel_start (struct sbmac_softc*) ; 
 int /*<<< orphan*/  sbmac_channel_stop (struct sbmac_softc*) ; 
 int sbmac_state_on ; 

__attribute__((used)) static enum sbmac_state sbmac_set_channel_state(struct sbmac_softc *sc,
						enum sbmac_state state)
{
	enum sbmac_state oldstate = sc->sbm_state;

	/*
	 * If same as previous state, return
	 */

	if (state == oldstate) {
		return oldstate;
	}

	/*
	 * If new state is ON, turn channel on
	 */

	if (state == sbmac_state_on) {
		sbmac_channel_start(sc);
	}
	else {
		sbmac_channel_stop(sc);
	}

	/*
	 * Return previous state
	 */

	return oldstate;
}