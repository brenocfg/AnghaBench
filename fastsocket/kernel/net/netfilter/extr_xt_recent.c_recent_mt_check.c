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
struct xt_recent_mtinfo {int check_set; scalar_t__ hit_count; char* name; scalar_t__ seconds; } ;
struct xt_mtchk_param {struct xt_recent_mtinfo* matchinfo; } ;
struct recent_table {int refcnt; int /*<<< orphan*/  list; int /*<<< orphan*/  name; int /*<<< orphan*/ * iphash; int /*<<< orphan*/  lru_list; } ;
struct proc_dir_entry {void* gid; void* uid; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int XT_RECENT_CHECK ; 
 scalar_t__ XT_RECENT_NAME_LEN ; 
 int XT_RECENT_REMOVE ; 
 int XT_RECENT_SET ; 
 int XT_RECENT_UPDATE ; 
 int hweight8 (int) ; 
 void* ip_list_gid ; 
 int ip_list_hash_size ; 
 int /*<<< orphan*/  ip_list_perms ; 
 void* ip_list_uid ; 
 scalar_t__ ip_pkt_list_tot ; 
 int /*<<< orphan*/  kfree (struct recent_table*) ; 
 struct recent_table* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct proc_dir_entry* proc_create_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct recent_table*) ; 
 int /*<<< orphan*/  proc_old_dir ; 
 int /*<<< orphan*/  recent_lock ; 
 int /*<<< orphan*/  recent_mt_fops ; 
 int /*<<< orphan*/  recent_mutex ; 
 int /*<<< orphan*/  recent_old_fops ; 
 int /*<<< orphan*/  recent_proc_dir ; 
 struct recent_table* recent_table_lookup (char*) ; 
 int /*<<< orphan*/  remove_proc_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strnlen (char*,scalar_t__) ; 
 int /*<<< orphan*/  tables ; 

__attribute__((used)) static bool recent_mt_check(const struct xt_mtchk_param *par)
{
	const struct xt_recent_mtinfo *info = par->matchinfo;
	struct recent_table *t;
#ifdef CONFIG_PROC_FS
	struct proc_dir_entry *pde;
#endif
	unsigned i;
	bool ret = false;

	if (hweight8(info->check_set &
		     (XT_RECENT_SET | XT_RECENT_REMOVE |
		      XT_RECENT_CHECK | XT_RECENT_UPDATE)) != 1)
		return false;
	if ((info->check_set & (XT_RECENT_SET | XT_RECENT_REMOVE)) &&
	    (info->seconds || info->hit_count))
		return false;
	if (info->hit_count > ip_pkt_list_tot)
		return false;
	if (info->name[0] == '\0' ||
	    strnlen(info->name, XT_RECENT_NAME_LEN) == XT_RECENT_NAME_LEN)
		return false;

	mutex_lock(&recent_mutex);
	t = recent_table_lookup(info->name);
	if (t != NULL) {
		t->refcnt++;
		ret = true;
		goto out;
	}

	t = kzalloc(sizeof(*t) + sizeof(t->iphash[0]) * ip_list_hash_size,
		    GFP_KERNEL);
	if (t == NULL)
		goto out;
	t->refcnt = 1;
	strcpy(t->name, info->name);
	INIT_LIST_HEAD(&t->lru_list);
	for (i = 0; i < ip_list_hash_size; i++)
		INIT_LIST_HEAD(&t->iphash[i]);
#ifdef CONFIG_PROC_FS
	pde = proc_create_data(t->name, ip_list_perms, recent_proc_dir,
		  &recent_mt_fops, t);
	if (pde == NULL) {
		kfree(t);
		goto out;
	}
	pde->uid = ip_list_uid;
	pde->gid = ip_list_gid;
#ifdef CONFIG_NETFILTER_XT_MATCH_RECENT_PROC_COMPAT
	pde = proc_create_data(t->name, ip_list_perms, proc_old_dir,
		      &recent_old_fops, t);
	if (pde == NULL) {
		remove_proc_entry(t->name, proc_old_dir);
		kfree(t);
		goto out;
	}
	pde->uid = ip_list_uid;
	pde->gid = ip_list_gid;
#endif
#endif
	spin_lock_bh(&recent_lock);
	list_add_tail(&t->list, &tables);
	spin_unlock_bh(&recent_lock);
	ret = true;
out:
	mutex_unlock(&recent_mutex);
	return ret;
}