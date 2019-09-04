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
typedef  int /*<<< orphan*/  tsd_t ;
typedef  int /*<<< orphan*/  quarantine_t ;

/* Variables and functions */
 int /*<<< orphan*/  config_fill ; 
 int /*<<< orphan*/  idalloctm (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  quarantine_drain (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcache_get (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * tsd_quarantine_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsd_quarantine_set (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
quarantine_cleanup(tsd_t *tsd)
{
	quarantine_t *quarantine;

	if (!config_fill)
		return;

	quarantine = tsd_quarantine_get(tsd);
	if (quarantine != NULL) {
		quarantine_drain(tsd, quarantine, 0);
		idalloctm(tsd, quarantine, tcache_get(tsd, false), true);
		tsd_quarantine_set(tsd, NULL);
	}
}