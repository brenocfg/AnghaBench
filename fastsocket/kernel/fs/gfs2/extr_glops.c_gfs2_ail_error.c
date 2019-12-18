#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  ln_number; int /*<<< orphan*/  ln_type; } ;
struct gfs2_glock {TYPE_1__ gl_name; int /*<<< orphan*/  gl_sbd; } ;
struct buffer_head {TYPE_2__* b_page; int /*<<< orphan*/  b_state; scalar_t__ b_blocknr; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  mapping; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  fs_err (int /*<<< orphan*/ ,char*,struct buffer_head const*,unsigned long long,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  gfs2_glock2aspace (struct gfs2_glock*) ; 

__attribute__((used)) static void gfs2_ail_error(struct gfs2_glock *gl, const struct buffer_head *bh)
{
	fs_err(gl->gl_sbd, "AIL buffer %p: blocknr %llu state 0x%08lx mapping %p page state 0x%lx\n",
	       bh, (unsigned long long)bh->b_blocknr, bh->b_state,
	       bh->b_page->mapping, bh->b_page->flags);
	fs_err(gl->gl_sbd, "AIL glock %u:%llu mapping %p\n",
	       gl->gl_name.ln_type, gl->gl_name.ln_number,
	       gfs2_glock2aspace(gl));
	BUG();
	/*gfs2_lm_withdraw(gl->gl_sbd, "AIL error\n");*/
}