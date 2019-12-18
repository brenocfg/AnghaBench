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
struct TYPE_2__ {int /*<<< orphan*/ * c_first_suballocator; } ;
struct ocfs2_truncate_context {int /*<<< orphan*/  tc_last_eb_bh; TYPE_1__ tc_dealloc; } ;

/* Variables and functions */
 int /*<<< orphan*/  ML_NOTICE ; 
 int /*<<< orphan*/  brelse (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ocfs2_truncate_context*) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void ocfs2_free_truncate_context(struct ocfs2_truncate_context *tc)
{
	/*
	 * The caller is responsible for completing deallocation
	 * before freeing the context.
	 */
	if (tc->tc_dealloc.c_first_suballocator != NULL)
		mlog(ML_NOTICE,
		     "Truncate completion has non-empty dealloc context\n");

	brelse(tc->tc_last_eb_bh);

	kfree(tc);
}