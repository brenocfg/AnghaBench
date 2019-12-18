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
struct dlm_rsb {int dummy; } ;
struct dlm_ls {TYPE_1__* ls_rsbtbl; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int _search_rsb (struct dlm_ls*,char*,int,int,unsigned int,struct dlm_rsb**) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int search_rsb(struct dlm_ls *ls, char *name, int len, int b,
		      unsigned int flags, struct dlm_rsb **r_ret)
{
	int error;
	spin_lock(&ls->ls_rsbtbl[b].lock);
	error = _search_rsb(ls, name, len, b, flags, r_ret);
	spin_unlock(&ls->ls_rsbtbl[b].lock);
	return error;
}