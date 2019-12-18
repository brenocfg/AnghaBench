#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  size_t uint16_t ;
struct dlm_ls {size_t ls_lkbtbl_size; TYPE_1__* ls_lkbtbl; } ;
struct dlm_lkb {int /*<<< orphan*/  lkb_ref; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EBADSLT ; 
 int ENOENT ; 
 struct dlm_lkb* __find_lkb (struct dlm_ls*,int) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int find_lkb(struct dlm_ls *ls, uint32_t lkid, struct dlm_lkb **lkb_ret)
{
	struct dlm_lkb *lkb;
	uint16_t bucket = (lkid >> 16);

	if (bucket >= ls->ls_lkbtbl_size)
		return -EBADSLT;

	read_lock(&ls->ls_lkbtbl[bucket].lock);
	lkb = __find_lkb(ls, lkid);
	if (lkb)
		kref_get(&lkb->lkb_ref);
	read_unlock(&ls->ls_lkbtbl[bucket].lock);

	*lkb_ret = lkb;
	return lkb ? 0 : -ENOENT;
}