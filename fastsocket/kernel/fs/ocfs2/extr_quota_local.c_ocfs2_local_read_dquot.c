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
struct dquot {int /*<<< orphan*/  dq_type; int /*<<< orphan*/  dq_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlog_entry (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  mlog_exit (int) ; 
 int ocfs2_create_local_dquot (struct dquot*) ; 
 int ocfs2_global_read_dquot (struct dquot*) ; 

__attribute__((used)) static int ocfs2_local_read_dquot(struct dquot *dquot)
{
	int status;

	mlog_entry("id=%u, type=%d\n", dquot->dq_id, dquot->dq_type);

	status = ocfs2_global_read_dquot(dquot);
	if (status < 0) {
		mlog_errno(status);
		goto out_err;
	}

	/* Now create entry in the local quota file */
	status = ocfs2_create_local_dquot(dquot);
	if (status < 0) {
		mlog_errno(status);
		goto out_err;
	}
	mlog_exit(0);
	return 0;
out_err:
	mlog_exit(status);
	return status;
}