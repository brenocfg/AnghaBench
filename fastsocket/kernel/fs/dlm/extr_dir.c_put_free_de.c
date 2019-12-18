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
struct dlm_ls {int /*<<< orphan*/  ls_recover_list_lock; int /*<<< orphan*/  ls_recover_list; } ;
struct dlm_direntry {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void put_free_de(struct dlm_ls *ls, struct dlm_direntry *de)
{
	spin_lock(&ls->ls_recover_list_lock);
	list_add(&de->list, &ls->ls_recover_list);
	spin_unlock(&ls->ls_recover_list_lock);
}