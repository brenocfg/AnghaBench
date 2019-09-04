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
struct nwk_wq_entry {int dummy; } ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct nwk_wq_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nwk_wq_head ; 
 int /*<<< orphan*/  nwk_wq_link ; 
 int /*<<< orphan*/  nwk_wq_lock ; 
 int /*<<< orphan*/  nwk_wq_waitch ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ ) ; 

void
nwk_wq_enqueue(struct nwk_wq_entry *nwk_item)
{
	lck_mtx_lock(&nwk_wq_lock);
	TAILQ_INSERT_TAIL(&nwk_wq_head, nwk_item, nwk_wq_link);
	lck_mtx_unlock(&nwk_wq_lock);
	wakeup((caddr_t)&nwk_wq_waitch);
}