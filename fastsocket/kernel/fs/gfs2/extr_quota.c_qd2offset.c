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
typedef  int u64 ;
struct gfs2_quota_data {int /*<<< orphan*/  qd_flags; scalar_t__ qd_id; } ;
struct gfs2_quota {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  QDF_USER ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static u64 qd2offset(struct gfs2_quota_data *qd)
{
	u64 offset;

	offset = 2 * (u64)qd->qd_id + !test_bit(QDF_USER, &qd->qd_flags);
	offset *= sizeof(struct gfs2_quota);

	return offset;
}