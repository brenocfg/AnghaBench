#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  time_t ;
struct tm {int dummy; } ;
typedef  int /*<<< orphan*/  nvlist_t ;
struct TYPE_3__ {int /*<<< orphan*/  libzfs_printerr; } ;
typedef  TYPE_1__ libzfs_handle_t ;
typedef  int int64_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  TEXT_DOMAIN ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_LOAD_INFO ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_LOAD_TIME ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_REWIND_INFO ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_REWIND_TIME ; 
 char* dgettext (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * localtime_r (int /*<<< orphan*/ *,struct tm*) ; 
 int /*<<< orphan*/  nvlist_lookup_int64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ nvlist_lookup_nvlist (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ nvlist_lookup_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ strftime (char*,int,int /*<<< orphan*/ ,struct tm*) ; 

__attribute__((used)) static void
zpool_rewind_exclaim(libzfs_handle_t *hdl, const char *name, boolean_t dryrun,
    nvlist_t *config)
{
	nvlist_t *nv = NULL;
	uint64_t rewindto;
	int64_t loss = -1;
	struct tm t;
	char timestr[128];

	if (!hdl->libzfs_printerr || config == NULL)
		return;

	if (nvlist_lookup_nvlist(config, ZPOOL_CONFIG_LOAD_INFO, &nv) != 0 ||
	    nvlist_lookup_nvlist(nv, ZPOOL_CONFIG_REWIND_INFO, &nv) != 0) {
		return;
	}

	if (nvlist_lookup_uint64(nv, ZPOOL_CONFIG_LOAD_TIME, &rewindto) != 0)
		return;
	(void) nvlist_lookup_int64(nv, ZPOOL_CONFIG_REWIND_TIME, &loss);

	if (localtime_r((time_t *)&rewindto, &t) != NULL &&
	    strftime(timestr, 128, 0, &t) != 0) {
		if (dryrun) {
			(void) printf(dgettext(TEXT_DOMAIN,
			    "Would be able to return %s "
			    "to its state as of %s.\n"),
			    name, timestr);
		} else {
			(void) printf(dgettext(TEXT_DOMAIN,
			    "Pool %s returned to its state as of %s.\n"),
			    name, timestr);
		}
		if (loss > 120) {
			(void) printf(dgettext(TEXT_DOMAIN,
			    "%s approximately %lld "),
			    dryrun ? "Would discard" : "Discarded",
			    (loss + 30) / 60);
			(void) printf(dgettext(TEXT_DOMAIN,
			    "minutes of transactions.\n"));
		} else if (loss > 0) {
			(void) printf(dgettext(TEXT_DOMAIN,
			    "%s approximately %lld "),
			    dryrun ? "Would discard" : "Discarded", loss);
			(void) printf(dgettext(TEXT_DOMAIN,
			    "seconds of transactions.\n"));
		}
	}
}