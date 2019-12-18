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
struct log_c {char* usr_argv_str; int /*<<< orphan*/  luid; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMERR (char*,...) ; 
 int /*<<< orphan*/  DMINFO (char*) ; 
 int /*<<< orphan*/  DMWARN (char*) ; 
 int DM_ULOG_CTR ; 
 int DM_ULOG_RESUME ; 
 int ESRCH ; 
 int HZ ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int dm_consult_userspace (char const*,int /*<<< orphan*/ ,int,char*,int,char*,size_t*) ; 
 int /*<<< orphan*/  schedule_timeout (int) ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 

__attribute__((used)) static int userspace_do_request(struct log_c *lc, const char *uuid,
				int request_type, char *data, size_t data_size,
				char *rdata, size_t *rdata_size)
{
	int r;

	/*
	 * If the server isn't there, -ESRCH is returned,
	 * and we must keep trying until the server is
	 * restored.
	 */
retry:
	r = dm_consult_userspace(uuid, lc->luid, request_type, data,
				 data_size, rdata, rdata_size);

	if (r != -ESRCH)
		return r;

	DMERR(" Userspace log server not found.");
	while (1) {
		set_current_state(TASK_INTERRUPTIBLE);
		schedule_timeout(2*HZ);
		DMWARN("Attempting to contact userspace log server...");
		r = dm_consult_userspace(uuid, lc->luid, DM_ULOG_CTR,
					 lc->usr_argv_str,
					 strlen(lc->usr_argv_str) + 1,
					 NULL, NULL);
		if (!r)
			break;
	}
	DMINFO("Reconnected to userspace log server... DM_ULOG_CTR complete");
	r = dm_consult_userspace(uuid, lc->luid, DM_ULOG_RESUME, NULL,
				 0, NULL, NULL);
	if (!r)
		goto retry;

	DMERR("Error trying to resume userspace log: %d", r);

	return -ESRCH;
}