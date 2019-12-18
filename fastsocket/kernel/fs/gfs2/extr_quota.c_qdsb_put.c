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
struct gfs2_quota_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bh_put (struct gfs2_quota_data*) ; 
 int /*<<< orphan*/  qd_put (struct gfs2_quota_data*) ; 
 int /*<<< orphan*/  slot_put (struct gfs2_quota_data*) ; 

__attribute__((used)) static void qdsb_put(struct gfs2_quota_data *qd)
{
	bh_put(qd);
	slot_put(qd);
	qd_put(qd);
}