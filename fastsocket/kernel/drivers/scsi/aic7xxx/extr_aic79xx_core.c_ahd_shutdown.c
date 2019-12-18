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
struct ahd_softc {int /*<<< orphan*/  stat_timer; int /*<<< orphan*/  reset_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  ahd_reset (struct ahd_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_timer_stop (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ahd_shutdown(void *arg)
{
	struct	ahd_softc *ahd;

	ahd = (struct ahd_softc *)arg;

	/*
	 * Stop periodic timer callbacks.
	 */
	ahd_timer_stop(&ahd->reset_timer);
	ahd_timer_stop(&ahd->stat_timer);

	/* This will reset most registers to 0, but not all */
	ahd_reset(ahd, /*reinit*/FALSE);
}