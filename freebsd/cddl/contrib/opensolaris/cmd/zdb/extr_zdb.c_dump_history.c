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
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  unsigned int uint_t ;
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ time_t ;
typedef  int /*<<< orphan*/  tbuf ;
struct tm {int dummy; } ;
typedef  int /*<<< orphan*/  spa_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  internalstr ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 scalar_t__ HIS_BUF_LEN_DEF ; 
 scalar_t__ HIS_BUF_LEN_MAX ; 
 int MAXPATHLEN ; 
 scalar_t__ ZFS_NUM_LEGACY_HISTORY_EVENTS ; 
 int /*<<< orphan*/  ZPOOL_HIST_CMD ; 
 int /*<<< orphan*/  ZPOOL_HIST_INT_EVENT ; 
 int /*<<< orphan*/  ZPOOL_HIST_INT_STR ; 
 int /*<<< orphan*/  ZPOOL_HIST_TIME ; 
 int /*<<< orphan*/  ZPOOL_HIST_TXG ; 
 int /*<<< orphan*/  dump_nvlist (int /*<<< orphan*/ *,int) ; 
 int* dump_opt ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  localtime_r (scalar_t__*,struct tm*) ; 
 char* malloc (scalar_t__) ; 
 scalar_t__ nvlist_lookup_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**) ; 
 scalar_t__ nvlist_lookup_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,int /*<<< orphan*/ ,char*) ; 
 int spa_history_get (int /*<<< orphan*/ *,scalar_t__*,scalar_t__*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strftime (char*,int,char*,struct tm*) ; 
 int /*<<< orphan*/  verify (int) ; 
 char** zfs_history_event_names ; 
 scalar_t__ zpool_history_unpack (char*,scalar_t__,scalar_t__*,int /*<<< orphan*/ ***,unsigned int*) ; 

__attribute__((used)) static void
dump_history(spa_t *spa)
{
	nvlist_t **events = NULL;
	char *buf = NULL;
	uint64_t bufsize = HIS_BUF_LEN_DEF;
	uint64_t resid, len, off = 0;
	uint_t num = 0;
	int error;
	time_t tsec;
	struct tm t;
	char tbuf[30];
	char internalstr[MAXPATHLEN];

	if ((buf = malloc(bufsize)) == NULL)
		(void) fprintf(stderr, "Unable to read history: "
		    "out of memory\n");
	do {
		len = bufsize;

		if ((error = spa_history_get(spa, &off, &len, buf)) != 0) {
			(void) fprintf(stderr, "Unable to read history: "
			    "error %d\n", error);
			return;
		}

		if (zpool_history_unpack(buf, len, &resid, &events, &num) != 0)
			break;
		off -= resid;

		/*
		 * If the history block is too big, double the buffer
		 * size and try again.
		 */
		if (resid == len) {
			free(buf);
			buf = NULL;

			bufsize <<= 1;
			if ((bufsize >= HIS_BUF_LEN_MAX) ||
			    ((buf = malloc(bufsize)) == NULL)) {
				(void) fprintf(stderr, "Unable to read history: "
				    "out of memory\n");
				return;
			}
		}
	} while (len != 0);
	free(buf);

	(void) printf("\nHistory:\n");
	for (unsigned i = 0; i < num; i++) {
		uint64_t time, txg, ievent;
		char *cmd, *intstr;
		boolean_t printed = B_FALSE;

		if (nvlist_lookup_uint64(events[i], ZPOOL_HIST_TIME,
		    &time) != 0)
			goto next;
		if (nvlist_lookup_string(events[i], ZPOOL_HIST_CMD,
		    &cmd) != 0) {
			if (nvlist_lookup_uint64(events[i],
			    ZPOOL_HIST_INT_EVENT, &ievent) != 0)
				goto next;
			verify(nvlist_lookup_uint64(events[i],
			    ZPOOL_HIST_TXG, &txg) == 0);
			verify(nvlist_lookup_string(events[i],
			    ZPOOL_HIST_INT_STR, &intstr) == 0);
			if (ievent >= ZFS_NUM_LEGACY_HISTORY_EVENTS)
				goto next;

			(void) snprintf(internalstr,
			    sizeof (internalstr),
			    "[internal %s txg:%ju] %s",
			    zfs_history_event_names[ievent], (uintmax_t)txg,
			    intstr);
			cmd = internalstr;
		}
		tsec = time;
		(void) localtime_r(&tsec, &t);
		(void) strftime(tbuf, sizeof (tbuf), "%F.%T", &t);
		(void) printf("%s %s\n", tbuf, cmd);
		printed = B_TRUE;

next:
		if (dump_opt['h'] > 1) {
			if (!printed)
				(void) printf("unrecognized record:\n");
			dump_nvlist(events[i], 2);
		}
	}
}