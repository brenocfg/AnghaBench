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
typedef  int /*<<< orphan*/  tcache_t ;

/* Variables and functions */
 int /*<<< orphan*/  config_tcache ; 
 int /*<<< orphan*/  tcache_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * tsd_tcache_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsd_tcache_set (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
tcache_cleanup(tsd_t *tsd)
{
	tcache_t *tcache;

	if (!config_tcache)
		return;

	if ((tcache = tsd_tcache_get(tsd)) != NULL) {
		tcache_destroy(tsd, tcache);
		tsd_tcache_set(tsd, NULL);
	}
}