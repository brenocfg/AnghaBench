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
struct policydb {int dummy; } ;
struct mls_range {int /*<<< orphan*/ * level; } ;

/* Variables and functions */
 scalar_t__ mls_level_dom (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ mls_level_isvalid (struct policydb*,int /*<<< orphan*/ *) ; 

int mls_range_isvalid(struct policydb *p, struct mls_range *r)
{
	return (mls_level_isvalid(p, &r->level[0]) &&
		mls_level_isvalid(p, &r->level[1]) &&
		mls_level_dom(&r->level[1], &r->level[0]));
}