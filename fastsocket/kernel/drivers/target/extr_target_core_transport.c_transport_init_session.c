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
struct se_session {int /*<<< orphan*/  sess_kref; int /*<<< orphan*/  sess_cmd_lock; int /*<<< orphan*/  sess_wait_list; int /*<<< orphan*/  sess_cmd_list; int /*<<< orphan*/  sess_acl_list; int /*<<< orphan*/  sess_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct se_session* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct se_session* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  se_sess_cache ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct se_session *transport_init_session(void)
{
	struct se_session *se_sess;

	se_sess = kmem_cache_zalloc(se_sess_cache, GFP_KERNEL);
	if (!se_sess) {
		pr_err("Unable to allocate struct se_session from"
				" se_sess_cache\n");
		return ERR_PTR(-ENOMEM);
	}
	INIT_LIST_HEAD(&se_sess->sess_list);
	INIT_LIST_HEAD(&se_sess->sess_acl_list);
	INIT_LIST_HEAD(&se_sess->sess_cmd_list);
	INIT_LIST_HEAD(&se_sess->sess_wait_list);
	spin_lock_init(&se_sess->sess_cmd_lock);
	kref_init(&se_sess->sess_kref);

	return se_sess;
}