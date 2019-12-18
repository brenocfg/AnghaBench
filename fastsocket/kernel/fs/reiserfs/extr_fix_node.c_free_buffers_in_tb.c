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
struct tree_balance {int /*<<< orphan*/ ** CFR; int /*<<< orphan*/ ** CFL; int /*<<< orphan*/ ** FR; int /*<<< orphan*/ ** FL; int /*<<< orphan*/ ** R; int /*<<< orphan*/ ** L; int /*<<< orphan*/  tb_path; } ;

/* Variables and functions */
 int MAX_HEIGHT ; 
 int /*<<< orphan*/  brelse (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pathrelse (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_buffers_in_tb(struct tree_balance *tb)
{
	int i;

	pathrelse(tb->tb_path);

	for (i = 0; i < MAX_HEIGHT; i++) {
		brelse(tb->L[i]);
		brelse(tb->R[i]);
		brelse(tb->FL[i]);
		brelse(tb->FR[i]);
		brelse(tb->CFL[i]);
		brelse(tb->CFR[i]);

		tb->L[i] = NULL;
		tb->R[i] = NULL;
		tb->FL[i] = NULL;
		tb->FR[i] = NULL;
		tb->CFL[i] = NULL;
		tb->CFR[i] = NULL;
	}
}