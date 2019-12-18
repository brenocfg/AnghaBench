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
struct ubifs_inode {int /*<<< orphan*/  data_len; } ;
struct ubifs_info {scalar_t__ inode_budget; } ;
struct ubifs_budget_req {scalar_t__ dd_growth; } ;

/* Variables and functions */
 scalar_t__ ALIGN (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct ubifs_budget_req*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ubifs_release_budget (struct ubifs_info*,struct ubifs_budget_req*) ; 

void ubifs_release_dirty_inode_budget(struct ubifs_info *c,
				      struct ubifs_inode *ui)
{
	struct ubifs_budget_req req;

	memset(&req, 0, sizeof(struct ubifs_budget_req));
	/* The "no space" flags will be cleared because dd_growth is > 0 */
	req.dd_growth = c->inode_budget + ALIGN(ui->data_len, 8);
	ubifs_release_budget(c, &req);
}