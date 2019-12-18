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
typedef  int /*<<< orphan*/  time_t ;
typedef  int /*<<< orphan*/  space_buf ;
struct TYPE_3__ {scalar_t__ pcs_state; int /*<<< orphan*/  pcs_space; int /*<<< orphan*/  pcs_start_time; } ;
typedef  TYPE_1__ pool_checkpoint_stat_t ;

/* Variables and functions */
 scalar_t__ CS_CHECKPOINT_DISCARDING ; 
 scalar_t__ CS_CHECKPOINT_EXISTS ; 
 scalar_t__ CS_NONE ; 
 int /*<<< orphan*/  assert (int) ; 
 char* ctime (int /*<<< orphan*/ *) ; 
 char* gettext (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char* strlen (char*) ; 
 int /*<<< orphan*/  zfs_nicenum (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
print_checkpoint_status(pool_checkpoint_stat_t *pcs)
{
	time_t start;
	char space_buf[7];

	if (pcs == NULL || pcs->pcs_state == CS_NONE)
		return;

	(void) printf(gettext("checkpoint: "));

	start = pcs->pcs_start_time;
	zfs_nicenum(pcs->pcs_space, space_buf, sizeof (space_buf));

	if (pcs->pcs_state == CS_CHECKPOINT_EXISTS) {
		char *date = ctime(&start);

		/*
		 * ctime() adds a newline at the end of the generated
		 * string, thus the weird format specifier and the
		 * strlen() call used to chop it off from the output.
		 */
		(void) printf(gettext("created %.*s, consumes %s\n"),
		    strlen(date) - 1, date, space_buf);
		return;
	}

	assert(pcs->pcs_state == CS_CHECKPOINT_DISCARDING);

	(void) printf(gettext("discarding, %s remaining.\n"),
	    space_buf);
}