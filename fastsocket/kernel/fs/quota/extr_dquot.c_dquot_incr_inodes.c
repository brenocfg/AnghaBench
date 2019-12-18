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
struct TYPE_2__ {int /*<<< orphan*/  dqb_curinodes; } ;
struct dquot {TYPE_1__ dq_dqb; } ;
typedef  scalar_t__ qsize_t ;

/* Variables and functions */

__attribute__((used)) static inline void dquot_incr_inodes(struct dquot *dquot, qsize_t number)
{
	dquot->dq_dqb.dqb_curinodes += number;
}