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
typedef  int /*<<< orphan*/  spa_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  FTAG ; 
 scalar_t__ SPA_VERSION_FEATURES ; 
 int /*<<< orphan*/  fatal (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char const*,int) ; 
 int /*<<< orphan*/  import_pool (char const*,int /*<<< orphan*/ ) ; 
 int spa_open (char const*,int /*<<< orphan*/ **,void*) ; 
 scalar_t__ spa_version (int /*<<< orphan*/ *) ; 
 int strerror (int) ; 
 int /*<<< orphan*/  zfeature_checks_disable ; 

__attribute__((used)) static void
zhack_spa_open(const char *target, boolean_t readonly, void *tag, spa_t **spa)
{
	int err;

	import_pool(target, readonly);

	zfeature_checks_disable = B_TRUE;
	err = spa_open(target, spa, tag);
	zfeature_checks_disable = B_FALSE;

	if (err != 0)
		fatal(*spa, FTAG, "cannot open '%s': %s", target,
		    strerror(err));
	if (spa_version(*spa) < SPA_VERSION_FEATURES) {
		fatal(*spa, FTAG, "'%s' has version %d, features not enabled",
		    target, (int)spa_version(*spa));
	}
}