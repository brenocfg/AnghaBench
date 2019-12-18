#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_long ;
struct ahc_softc {TYPE_1__* platform_data; } ;
struct TYPE_2__ {scalar_t__ qfrozen; int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int /*<<< orphan*/  ahc_lock (struct ahc_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ahc_unlock (struct ahc_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsi_unblock_requests (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ahc_linux_release_simq(struct ahc_softc *ahc)
{
	u_long s;
	int    unblock_reqs;

	unblock_reqs = 0;
	ahc_lock(ahc, &s);
	if (ahc->platform_data->qfrozen > 0)
		ahc->platform_data->qfrozen--;
	if (ahc->platform_data->qfrozen == 0)
		unblock_reqs = 1;
	ahc_unlock(ahc, &s);
	/*
	 * There is still a race here.  The mid-layer
	 * should keep its own freeze count and use
	 * a bottom half handler to run the queues
	 * so we can unblock with our own lock held.
	 */
	if (unblock_reqs)
		scsi_unblock_requests(ahc->platform_data->host);
}