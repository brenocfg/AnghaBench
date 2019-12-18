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
typedef  int /*<<< orphan*/  zpool_handle_t ;
typedef  int uint_t ;
typedef  void* uid_t ;
typedef  void* time_t ;
typedef  int /*<<< orphan*/  tbuf ;
struct tm {int dummy; } ;
struct passwd {char* pw_name; } ;
typedef  int /*<<< orphan*/  nvlist_t ;
struct TYPE_2__ {int /*<<< orphan*/  longfmt; int /*<<< orphan*/  internal; int /*<<< orphan*/  first; } ;
typedef  TYPE_1__ hist_cbdata_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int ZFS_NUM_LEGACY_HISTORY_EVENTS ; 
 int /*<<< orphan*/  ZPOOL_HIST_CMD ; 
 int /*<<< orphan*/  ZPOOL_HIST_DSID ; 
 int /*<<< orphan*/  ZPOOL_HIST_DSNAME ; 
 int /*<<< orphan*/  ZPOOL_HIST_ERRNO ; 
 int /*<<< orphan*/  ZPOOL_HIST_HOST ; 
 int /*<<< orphan*/  ZPOOL_HIST_INPUT_NVL ; 
 int /*<<< orphan*/  ZPOOL_HIST_INT_EVENT ; 
 int /*<<< orphan*/  ZPOOL_HIST_INT_NAME ; 
 int /*<<< orphan*/  ZPOOL_HIST_INT_STR ; 
 int /*<<< orphan*/  ZPOOL_HIST_IOCTL ; 
 int /*<<< orphan*/  ZPOOL_HIST_OUTPUT_NVL ; 
 int /*<<< orphan*/  ZPOOL_HIST_RECORD ; 
 int /*<<< orphan*/  ZPOOL_HIST_TIME ; 
 int /*<<< orphan*/  ZPOOL_HIST_TXG ; 
 int /*<<< orphan*/  ZPOOL_HIST_WHO ; 
 int /*<<< orphan*/  ZPOOL_HIST_ZONE ; 
 int /*<<< orphan*/  dump_nvlist (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fnvlist_lookup_int64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fnvlist_lookup_nvlist (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* fnvlist_lookup_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* fnvlist_lookup_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct passwd* getpwuid (void*) ; 
 char* gettext (char*) ; 
 int /*<<< orphan*/  localtime_r (void**,struct tm*) ; 
 scalar_t__ nvlist_exists (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 scalar_t__ nvlist_lookup_nvlist_array (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ***,int*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  strftime (char*,int,char*,struct tm*) ; 
 int /*<<< orphan*/  verify (int) ; 
 char** zfs_history_event_names ; 
 int zpool_get_history (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 char* zpool_get_name (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
get_history_one(zpool_handle_t *zhp, void *data)
{
	nvlist_t *nvhis;
	nvlist_t **records;
	uint_t numrecords;
	int ret, i;
	hist_cbdata_t *cb = (hist_cbdata_t *)data;

	cb->first = B_FALSE;

	(void) printf(gettext("History for '%s':\n"), zpool_get_name(zhp));

	if ((ret = zpool_get_history(zhp, &nvhis)) != 0)
		return (ret);

	verify(nvlist_lookup_nvlist_array(nvhis, ZPOOL_HIST_RECORD,
	    &records, &numrecords) == 0);
	for (i = 0; i < numrecords; i++) {
		nvlist_t *rec = records[i];
		char tbuf[30] = "";

		if (nvlist_exists(rec, ZPOOL_HIST_TIME)) {
			time_t tsec;
			struct tm t;

			tsec = fnvlist_lookup_uint64(records[i],
			    ZPOOL_HIST_TIME);
			(void) localtime_r(&tsec, &t);
			(void) strftime(tbuf, sizeof (tbuf), "%F.%T", &t);
		}

		if (nvlist_exists(rec, ZPOOL_HIST_CMD)) {
			(void) printf("%s %s", tbuf,
			    fnvlist_lookup_string(rec, ZPOOL_HIST_CMD));
		} else if (nvlist_exists(rec, ZPOOL_HIST_INT_EVENT)) {
			int ievent =
			    fnvlist_lookup_uint64(rec, ZPOOL_HIST_INT_EVENT);
			if (!cb->internal)
				continue;
			if (ievent >= ZFS_NUM_LEGACY_HISTORY_EVENTS) {
				(void) printf("%s unrecognized record:\n",
				    tbuf);
				dump_nvlist(rec, 4);
				continue;
			}
			(void) printf("%s [internal %s txg:%lld] %s", tbuf,
			    zfs_history_event_names[ievent],
			    fnvlist_lookup_uint64(rec, ZPOOL_HIST_TXG),
			    fnvlist_lookup_string(rec, ZPOOL_HIST_INT_STR));
		} else if (nvlist_exists(rec, ZPOOL_HIST_INT_NAME)) {
			if (!cb->internal)
				continue;
			(void) printf("%s [txg:%lld] %s", tbuf,
			    fnvlist_lookup_uint64(rec, ZPOOL_HIST_TXG),
			    fnvlist_lookup_string(rec, ZPOOL_HIST_INT_NAME));
			if (nvlist_exists(rec, ZPOOL_HIST_DSNAME)) {
				(void) printf(" %s (%llu)",
				    fnvlist_lookup_string(rec,
				    ZPOOL_HIST_DSNAME),
				    fnvlist_lookup_uint64(rec,
				    ZPOOL_HIST_DSID));
			}
			(void) printf(" %s", fnvlist_lookup_string(rec,
			    ZPOOL_HIST_INT_STR));
		} else if (nvlist_exists(rec, ZPOOL_HIST_IOCTL)) {
			if (!cb->internal)
				continue;
			(void) printf("%s ioctl %s\n", tbuf,
			    fnvlist_lookup_string(rec, ZPOOL_HIST_IOCTL));
			if (nvlist_exists(rec, ZPOOL_HIST_INPUT_NVL)) {
				(void) printf("    input:\n");
				dump_nvlist(fnvlist_lookup_nvlist(rec,
				    ZPOOL_HIST_INPUT_NVL), 8);
			}
			if (nvlist_exists(rec, ZPOOL_HIST_OUTPUT_NVL)) {
				(void) printf("    output:\n");
				dump_nvlist(fnvlist_lookup_nvlist(rec,
				    ZPOOL_HIST_OUTPUT_NVL), 8);
			}
			if (nvlist_exists(rec, ZPOOL_HIST_ERRNO)) {
				(void) printf("    errno: %lld\n",
				    fnvlist_lookup_int64(rec,
				    ZPOOL_HIST_ERRNO));
			}
		} else {
			if (!cb->internal)
				continue;
			(void) printf("%s unrecognized record:\n", tbuf);
			dump_nvlist(rec, 4);
		}

		if (!cb->longfmt) {
			(void) printf("\n");
			continue;
		}
		(void) printf(" [");
		if (nvlist_exists(rec, ZPOOL_HIST_WHO)) {
			uid_t who = fnvlist_lookup_uint64(rec, ZPOOL_HIST_WHO);
			struct passwd *pwd = getpwuid(who);
			(void) printf("user %d ", (int)who);
			if (pwd != NULL)
				(void) printf("(%s) ", pwd->pw_name);
		}
		if (nvlist_exists(rec, ZPOOL_HIST_HOST)) {
			(void) printf("on %s",
			    fnvlist_lookup_string(rec, ZPOOL_HIST_HOST));
		}
		if (nvlist_exists(rec, ZPOOL_HIST_ZONE)) {
			(void) printf(":%s",
			    fnvlist_lookup_string(rec, ZPOOL_HIST_ZONE));
		}
		(void) printf("]");
		(void) printf("\n");
	}
	(void) printf("\n");
	nvlist_free(nvhis);

	return (ret);
}