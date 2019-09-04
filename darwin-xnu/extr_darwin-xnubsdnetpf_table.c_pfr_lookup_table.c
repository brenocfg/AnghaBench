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
struct pfr_table {int dummy; } ;
struct pfr_ktable {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 struct pfr_ktable* RB_FIND (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct pfr_ktable*) ; 
 int /*<<< orphan*/  pf_lock ; 
 int /*<<< orphan*/  pfr_ktablehead ; 
 int /*<<< orphan*/  pfr_ktables ; 

__attribute__((used)) static struct pfr_ktable *
pfr_lookup_table(struct pfr_table *tbl)
{
	LCK_MTX_ASSERT(pf_lock, LCK_MTX_ASSERT_OWNED);

	/* struct pfr_ktable start like a struct pfr_table */
	return (RB_FIND(pfr_ktablehead, &pfr_ktables,
	    (struct pfr_ktable *)(void *)tbl));
}