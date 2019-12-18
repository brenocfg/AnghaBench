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
typedef  int /*<<< orphan*/  u32 ;
struct gfs2_sbd {int dummy; } ;
struct gfs2_quota_data {int dummy; } ;

/* Variables and functions */
 int bh_get (struct gfs2_quota_data*) ; 
 int qd_get (struct gfs2_sbd*,int,int /*<<< orphan*/ ,struct gfs2_quota_data**) ; 
 int /*<<< orphan*/  qd_put (struct gfs2_quota_data*) ; 
 int slot_get (struct gfs2_quota_data*) ; 
 int /*<<< orphan*/  slot_put (struct gfs2_quota_data*) ; 

__attribute__((used)) static int qdsb_get(struct gfs2_sbd *sdp, int user, u32 id,
		    struct gfs2_quota_data **qdp)
{
	int error;

	error = qd_get(sdp, user, id, qdp);
	if (error)
		return error;

	error = slot_get(*qdp);
	if (error)
		goto fail;

	error = bh_get(*qdp);
	if (error)
		goto fail_slot;

	return 0;

fail_slot:
	slot_put(*qdp);
fail:
	qd_put(*qdp);
	return error;
}