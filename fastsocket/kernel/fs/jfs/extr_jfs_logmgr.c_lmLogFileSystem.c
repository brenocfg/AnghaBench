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
struct logsuper {TYPE_1__* active; } ;
struct lbuf {scalar_t__ l_ldata; } ;
struct jfs_sb_info {char* uuid; int aggregate; } ;
struct jfs_log {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  uuid; } ;

/* Variables and functions */
 int EIO ; 
 int EMFILE ; 
 int MAX_ACTIVE ; 
 char* NULL_UUID ; 
 int /*<<< orphan*/  jfs_warn (char*) ; 
 int /*<<< orphan*/  lbmDirectWrite (struct jfs_log*,struct lbuf*,int) ; 
 int /*<<< orphan*/  lbmFREE ; 
 int /*<<< orphan*/  lbmFree (struct lbuf*) ; 
 int lbmIOWait (struct lbuf*,int /*<<< orphan*/ ) ; 
 int lbmRELEASE ; 
 int lbmRead (struct jfs_log*,int,struct lbuf**) ; 
 int lbmSYNC ; 
 int lbmWRITE ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int lmLogFileSystem(struct jfs_log * log, struct jfs_sb_info *sbi,
			   int activate)
{
	int rc = 0;
	int i;
	struct logsuper *logsuper;
	struct lbuf *bpsuper;
	char *uuid = sbi->uuid;

	/*
	 * insert/remove file system device to log active file system list.
	 */
	if ((rc = lbmRead(log, 1, &bpsuper)))
		return rc;

	logsuper = (struct logsuper *) bpsuper->l_ldata;
	if (activate) {
		for (i = 0; i < MAX_ACTIVE; i++)
			if (!memcmp(logsuper->active[i].uuid, NULL_UUID, 16)) {
				memcpy(logsuper->active[i].uuid, uuid, 16);
				sbi->aggregate = i;
				break;
			}
		if (i == MAX_ACTIVE) {
			jfs_warn("Too many file systems sharing journal!");
			lbmFree(bpsuper);
			return -EMFILE;	/* Is there a better rc? */
		}
	} else {
		for (i = 0; i < MAX_ACTIVE; i++)
			if (!memcmp(logsuper->active[i].uuid, uuid, 16)) {
				memcpy(logsuper->active[i].uuid, NULL_UUID, 16);
				break;
			}
		if (i == MAX_ACTIVE) {
			jfs_warn("Somebody stomped on the journal!");
			lbmFree(bpsuper);
			return -EIO;
		}

	}

	/*
	 * synchronous write log superblock:
	 *
	 * write sidestream bypassing write queue:
	 * at file system mount, log super block is updated for
	 * activation of the file system before any log record
	 * (MOUNT record) of the file system, and at file system
	 * unmount, all meta data for the file system has been
	 * flushed before log super block is updated for deactivation
	 * of the file system.
	 */
	lbmDirectWrite(log, bpsuper, lbmWRITE | lbmRELEASE | lbmSYNC);
	rc = lbmIOWait(bpsuper, lbmFREE);

	return rc;
}