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
struct tree_balance {int /*<<< orphan*/ ** FL; int /*<<< orphan*/  tb_path; } ;

/* Variables and functions */
 int B_NR_ITEMS (int /*<<< orphan*/ *) ; 
 int PATH_H_POSITION (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * PATH_H_PPARENT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RFALSE (int,char*,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

int get_left_neighbor_position(struct tree_balance *tb, int h)
{
	int Sh_position = PATH_H_POSITION(tb->tb_path, h + 1);

	RFALSE(PATH_H_PPARENT(tb->tb_path, h) == NULL || tb->FL[h] == NULL,
	       "vs-12325: FL[%d](%p) or F[%d](%p) does not exist",
	       h, tb->FL[h], h, PATH_H_PPARENT(tb->tb_path, h));

	if (Sh_position == 0)
		return B_NR_ITEMS(tb->FL[h]);
	else
		return Sh_position - 1;
}