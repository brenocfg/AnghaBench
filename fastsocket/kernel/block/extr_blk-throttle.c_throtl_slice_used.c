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
struct throtl_grp {int /*<<< orphan*/ * slice_end; int /*<<< orphan*/ * slice_start; } ;
struct throtl_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  jiffies ; 
 scalar_t__ time_in_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
throtl_slice_used(struct throtl_data *td, struct throtl_grp *tg, bool rw)
{
	if (time_in_range(jiffies, tg->slice_start[rw], tg->slice_end[rw]))
		return 0;

	return 1;
}