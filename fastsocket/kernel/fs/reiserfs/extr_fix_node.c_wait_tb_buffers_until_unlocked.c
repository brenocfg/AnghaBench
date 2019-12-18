#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tree_balance {int /*<<< orphan*/  tb_sb; struct buffer_head** FEB; struct buffer_head** CFR; struct buffer_head** FR; struct buffer_head** R; scalar_t__* rnum; struct buffer_head** CFL; struct buffer_head** FL; struct buffer_head** L; scalar_t__* lnum; scalar_t__* insert_size; TYPE_1__* tb_path; } ;
struct buffer_head {int dummy; } ;
struct TYPE_3__ {int path_length; } ;

/* Variables and functions */
 int CARRY_ON ; 
 scalar_t__ FILESYSTEM_CHANGED_TB (struct tree_balance*) ; 
 int ILLEGAL_PATH_ELEMENT_OFFSET ; 
 int MAX_FEB_SIZE ; 
 int MAX_HEIGHT ; 
 struct buffer_head* PATH_OFFSET_PBUFFER (TYPE_1__*,int) ; 
 struct buffer_head* PATH_PLAST_BUFFER (TYPE_1__*) ; 
 int REPEAT_SEARCH ; 
 int /*<<< orphan*/  __wait_on_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  clear_all_dirty_bits (int /*<<< orphan*/ ,struct buffer_head*) ; 
 int /*<<< orphan*/  reiserfs_warning (int /*<<< orphan*/ ,char*,char*,struct buffer_head*) ; 
 int /*<<< orphan*/  tb_buffer_sanity_check (int /*<<< orphan*/ ,struct buffer_head*,char*,int) ; 

__attribute__((used)) static int wait_tb_buffers_until_unlocked(struct tree_balance *tb)
{
	struct buffer_head *locked;
#ifdef CONFIG_REISERFS_CHECK
	int repeat_counter = 0;
#endif
	int i;

	do {

		locked = NULL;

		for (i = tb->tb_path->path_length;
		     !locked && i > ILLEGAL_PATH_ELEMENT_OFFSET; i--) {
			if (PATH_OFFSET_PBUFFER(tb->tb_path, i)) {
				/* if I understand correctly, we can only be sure the last buffer
				 ** in the path is in the tree --clm
				 */
#ifdef CONFIG_REISERFS_CHECK
				if (PATH_PLAST_BUFFER(tb->tb_path) ==
				    PATH_OFFSET_PBUFFER(tb->tb_path, i))
					tb_buffer_sanity_check(tb->tb_sb,
							       PATH_OFFSET_PBUFFER
							       (tb->tb_path,
								i), "S",
							       tb->tb_path->
							       path_length - i);
#endif
				if (!clear_all_dirty_bits(tb->tb_sb,
							  PATH_OFFSET_PBUFFER
							  (tb->tb_path,
							   i))) {
					locked =
					    PATH_OFFSET_PBUFFER(tb->tb_path,
								i);
				}
			}
		}

		for (i = 0; !locked && i < MAX_HEIGHT && tb->insert_size[i];
		     i++) {

			if (tb->lnum[i]) {

				if (tb->L[i]) {
					tb_buffer_sanity_check(tb->tb_sb,
							       tb->L[i],
							       "L", i);
					if (!clear_all_dirty_bits
					    (tb->tb_sb, tb->L[i]))
						locked = tb->L[i];
				}

				if (!locked && tb->FL[i]) {
					tb_buffer_sanity_check(tb->tb_sb,
							       tb->FL[i],
							       "FL", i);
					if (!clear_all_dirty_bits
					    (tb->tb_sb, tb->FL[i]))
						locked = tb->FL[i];
				}

				if (!locked && tb->CFL[i]) {
					tb_buffer_sanity_check(tb->tb_sb,
							       tb->CFL[i],
							       "CFL", i);
					if (!clear_all_dirty_bits
					    (tb->tb_sb, tb->CFL[i]))
						locked = tb->CFL[i];
				}

			}

			if (!locked && (tb->rnum[i])) {

				if (tb->R[i]) {
					tb_buffer_sanity_check(tb->tb_sb,
							       tb->R[i],
							       "R", i);
					if (!clear_all_dirty_bits
					    (tb->tb_sb, tb->R[i]))
						locked = tb->R[i];
				}

				if (!locked && tb->FR[i]) {
					tb_buffer_sanity_check(tb->tb_sb,
							       tb->FR[i],
							       "FR", i);
					if (!clear_all_dirty_bits
					    (tb->tb_sb, tb->FR[i]))
						locked = tb->FR[i];
				}

				if (!locked && tb->CFR[i]) {
					tb_buffer_sanity_check(tb->tb_sb,
							       tb->CFR[i],
							       "CFR", i);
					if (!clear_all_dirty_bits
					    (tb->tb_sb, tb->CFR[i]))
						locked = tb->CFR[i];
				}
			}
		}
		/* as far as I can tell, this is not required.  The FEB list seems
		 ** to be full of newly allocated nodes, which will never be locked,
		 ** dirty, or anything else.
		 ** To be safe, I'm putting in the checks and waits in.  For the moment,
		 ** they are needed to keep the code in journal.c from complaining
		 ** about the buffer.  That code is inside CONFIG_REISERFS_CHECK as well.
		 ** --clm
		 */
		for (i = 0; !locked && i < MAX_FEB_SIZE; i++) {
			if (tb->FEB[i]) {
				if (!clear_all_dirty_bits
				    (tb->tb_sb, tb->FEB[i]))
					locked = tb->FEB[i];
			}
		}

		if (locked) {
#ifdef CONFIG_REISERFS_CHECK
			repeat_counter++;
			if ((repeat_counter % 10000) == 0) {
				reiserfs_warning(tb->tb_sb, "reiserfs-8200",
						 "too many iterations waiting "
						 "for buffer to unlock "
						 "(%b)", locked);

				/* Don't loop forever.  Try to recover from possible error. */

				return (FILESYSTEM_CHANGED_TB(tb)) ?
				    REPEAT_SEARCH : CARRY_ON;
			}
#endif
			__wait_on_buffer(locked);
			if (FILESYSTEM_CHANGED_TB(tb))
				return REPEAT_SEARCH;
		}

	} while (locked);

	return CARRY_ON;
}