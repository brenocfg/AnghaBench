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
struct bnx2x_prev_path_list {scalar_t__ aer; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_DEV_INFO (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BP_PATH (struct bnx2x*) ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NETIF_MSG_HW ; 
 struct bnx2x_prev_path_list* bnx2x_prev_path_get_entry (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_prev_sem ; 
 scalar_t__ down_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool bnx2x_prev_is_path_marked(struct bnx2x *bp)
{
	struct bnx2x_prev_path_list *tmp_list;
	int rc = false;

	if (down_trylock(&bnx2x_prev_sem))
		return false;

	tmp_list = bnx2x_prev_path_get_entry(bp);
	if (tmp_list) {
		if (tmp_list->aer) {
			DP(NETIF_MSG_HW, "Path %d was marked by AER\n",
			   BP_PATH(bp));
		} else {
			rc = true;
			BNX2X_DEV_INFO("Path %d was already cleaned from previous drivers\n",
				       BP_PATH(bp));
		}
	}

	up(&bnx2x_prev_sem);

	return rc;
}