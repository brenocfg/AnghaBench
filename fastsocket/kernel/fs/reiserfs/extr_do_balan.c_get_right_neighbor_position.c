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
struct tree_balance {int /*<<< orphan*/  tb_path; int /*<<< orphan*/ ** FR; } ;

/* Variables and functions */
 int B_NR_ITEMS (int /*<<< orphan*/ *) ; 
 int PATH_H_POSITION (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * PATH_H_PPARENT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RFALSE (int,char*,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

int get_right_neighbor_position(struct tree_balance *tb, int h)
{
	int Sh_position = PATH_H_POSITION(tb->tb_path, h + 1);

	RFALSE(PATH_H_PPARENT(tb->tb_path, h) == NULL || tb->FR[h] == NULL,
	       "vs-12330: F[%d](%p) or FR[%d](%p) does not exist",
	       h, PATH_H_PPARENT(tb->tb_path, h), h, tb->FR[h]);

	if (Sh_position == B_NR_ITEMS(PATH_H_PPARENT(tb->tb_path, h)))
		return 0;
	else
		return Sh_position + 1;
}