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
struct tree_balance {int /*<<< orphan*/ ** CFR; int /*<<< orphan*/ * rkey; int /*<<< orphan*/ ** R; } ;
struct item_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  B_NR_ITEMS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  B_N_PDELIM_KEY (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KEY_SIZE ; 
 int /*<<< orphan*/  RFALSE (int,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  do_balance_mark_internal_dirty (struct tree_balance*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,struct item_head*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void replace_rkey(struct tree_balance *tb, int h, struct item_head *key)
{
	RFALSE(tb->R[h] == NULL || tb->CFR[h] == NULL,
	       "R[h](%p) and CFR[h](%p) must exist in replace_rkey",
	       tb->R[h], tb->CFR[h]);
	RFALSE(B_NR_ITEMS(tb->R[h]) == 0,
	       "R[h] can not be empty if it exists (item number=%d)",
	       B_NR_ITEMS(tb->R[h]));

	memcpy(B_N_PDELIM_KEY(tb->CFR[h], tb->rkey[h]), key, KEY_SIZE);

	do_balance_mark_internal_dirty(tb, tb->CFR[h], 0);
}