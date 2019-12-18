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
struct tree_balance {scalar_t__* R; scalar_t__* CFL; int* lkey; int /*<<< orphan*/  tb_path; } ;
struct buffer_info {scalar_t__ bi_bh; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int B_NR_ITEMS (scalar_t__) ; 
 int /*<<< orphan*/  LAST_TO_FIRST ; 
 scalar_t__ PATH_H_PBUFFER (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RFALSE (int,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  internal_define_dest_src_infos (int,struct tree_balance*,int,struct buffer_info*,struct buffer_info*,int*,struct buffer_head**) ; 
 int /*<<< orphan*/  internal_insert_key (struct buffer_info*,int /*<<< orphan*/ ,struct buffer_head*,int) ; 
 int /*<<< orphan*/  internal_move_pointers_items (struct buffer_info*,struct buffer_info*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  replace_key (struct tree_balance*,struct buffer_head*,int,scalar_t__,int) ; 

__attribute__((used)) static void internal_shift_right(int mode,	/* INTERNAL_FROM_S_TO_R | INTERNAL_FROM_L_TO_S */
				 struct tree_balance *tb,
				 int h, int pointer_amount)
{
	struct buffer_info dest_bi, src_bi;
	struct buffer_head *cf;
	int d_key_position;
	int nr;

	internal_define_dest_src_infos(mode, tb, h, &dest_bi, &src_bi,
				       &d_key_position, &cf);

	nr = B_NR_ITEMS(src_bi.bi_bh);

	if (pointer_amount > 0) {
		/* insert delimiting key from common father of dest and src to dest node into position 0 */
		internal_insert_key(&dest_bi, 0, cf, d_key_position);
		if (nr == pointer_amount - 1) {
			RFALSE(src_bi.bi_bh != PATH_H_PBUFFER(tb->tb_path, h) /*tb->S[h] */ ||
			       dest_bi.bi_bh != tb->R[h],
			       "src (%p) must be == tb->S[h](%p) when it disappears",
			       src_bi.bi_bh, PATH_H_PBUFFER(tb->tb_path, h));
			/* when S[h] disappers replace left delemiting key as well */
			if (tb->CFL[h])
				replace_key(tb, cf, d_key_position, tb->CFL[h],
					    tb->lkey[h]);
		} else
			replace_key(tb, cf, d_key_position, src_bi.bi_bh,
				    nr - pointer_amount);
	}

	/* last parameter is del_parameter */
	internal_move_pointers_items(&dest_bi, &src_bi, LAST_TO_FIRST,
				     pointer_amount, 0);
}