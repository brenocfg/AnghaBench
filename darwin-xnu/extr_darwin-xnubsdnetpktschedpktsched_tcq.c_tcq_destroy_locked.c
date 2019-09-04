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
struct tcq_if {int /*<<< orphan*/  tif_ifq; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFCQ_LOCK_ASSERT_HELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  TCQIF_IFP (struct tcq_if*) ; 
 int /*<<< orphan*/  if_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pktsched_verbose ; 
 int /*<<< orphan*/  tcq_clear_interface (struct tcq_if*) ; 
 int /*<<< orphan*/  tcq_style (struct tcq_if*) ; 
 int /*<<< orphan*/  tcq_zone ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ ,struct tcq_if*) ; 

__attribute__((used)) static int
tcq_destroy_locked(struct tcq_if *tif)
{
	IFCQ_LOCK_ASSERT_HELD(tif->tif_ifq);

	(void) tcq_clear_interface(tif);

	if (pktsched_verbose) {
		log(LOG_DEBUG, "%s: %s scheduler destroyed\n",
		    if_name(TCQIF_IFP(tif)), tcq_style(tif));
	}

	zfree(tcq_zone, tif);

	return (0);
}