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
struct dlm_rsb {int res_length; int /*<<< orphan*/  res_recover_list; int /*<<< orphan*/  res_root_list; int /*<<< orphan*/  res_waitqueue; int /*<<< orphan*/  res_convertqueue; int /*<<< orphan*/  res_grantqueue; int /*<<< orphan*/  res_lookup; int /*<<< orphan*/  res_mutex; int /*<<< orphan*/  res_name; struct dlm_ls* res_ls; } ;
struct dlm_ls {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct dlm_rsb* dlm_allocate_rsb (struct dlm_ls*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct dlm_rsb *create_rsb(struct dlm_ls *ls, char *name, int len)
{
	struct dlm_rsb *r;

	r = dlm_allocate_rsb(ls, len);
	if (!r)
		return NULL;

	r->res_ls = ls;
	r->res_length = len;
	memcpy(r->res_name, name, len);
	mutex_init(&r->res_mutex);

	INIT_LIST_HEAD(&r->res_lookup);
	INIT_LIST_HEAD(&r->res_grantqueue);
	INIT_LIST_HEAD(&r->res_convertqueue);
	INIT_LIST_HEAD(&r->res_waitqueue);
	INIT_LIST_HEAD(&r->res_root_list);
	INIT_LIST_HEAD(&r->res_recover_list);

	return r;
}