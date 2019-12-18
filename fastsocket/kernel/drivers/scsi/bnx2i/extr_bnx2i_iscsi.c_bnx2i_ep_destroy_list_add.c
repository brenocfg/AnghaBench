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
struct bnx2i_hba {int /*<<< orphan*/  ep_rdwr_lock; int /*<<< orphan*/  ep_destroy_list; } ;
struct bnx2i_endpoint {int /*<<< orphan*/  link; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bnx2i_ep_destroy_list_add(struct bnx2i_hba *hba,
				     struct bnx2i_endpoint *ep)
{
	write_lock_bh(&hba->ep_rdwr_lock);
	list_add_tail(&ep->link, &hba->ep_destroy_list);
	write_unlock_bh(&hba->ep_rdwr_lock);
	return 0;
}