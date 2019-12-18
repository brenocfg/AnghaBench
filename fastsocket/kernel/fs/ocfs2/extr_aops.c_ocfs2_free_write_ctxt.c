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
struct ocfs2_write_ctxt {int /*<<< orphan*/  w_di_bh; int /*<<< orphan*/  w_num_pages; int /*<<< orphan*/  w_pages; } ;

/* Variables and functions */
 int /*<<< orphan*/  brelse (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ocfs2_write_ctxt*) ; 
 int /*<<< orphan*/  ocfs2_unlock_and_free_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ocfs2_free_write_ctxt(struct ocfs2_write_ctxt *wc)
{
	ocfs2_unlock_and_free_pages(wc->w_pages, wc->w_num_pages);

	brelse(wc->w_di_bh);
	kfree(wc);
}