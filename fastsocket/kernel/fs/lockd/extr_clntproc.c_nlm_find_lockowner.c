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
struct nlm_lockowner {int /*<<< orphan*/  list; int /*<<< orphan*/  host; int /*<<< orphan*/  pid; int /*<<< orphan*/  owner; int /*<<< orphan*/  count; } ;
struct nlm_host {int /*<<< orphan*/  h_lock; int /*<<< orphan*/  h_lockowners; } ;
typedef  int /*<<< orphan*/  fl_owner_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  __nlm_alloc_pid (struct nlm_host*) ; 
 struct nlm_lockowner* __nlm_find_lockowner (struct nlm_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kfree (struct nlm_lockowner*) ; 
 struct nlm_lockowner* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nlm_get_host (struct nlm_host*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct nlm_lockowner *nlm_find_lockowner(struct nlm_host *host, fl_owner_t owner)
{
	struct nlm_lockowner *res, *new = NULL;

	spin_lock(&host->h_lock);
	res = __nlm_find_lockowner(host, owner);
	if (res == NULL) {
		spin_unlock(&host->h_lock);
		new = kmalloc(sizeof(*new), GFP_KERNEL);
		spin_lock(&host->h_lock);
		res = __nlm_find_lockowner(host, owner);
		if (res == NULL && new != NULL) {
			res = new;
			atomic_set(&new->count, 1);
			new->owner = owner;
			new->pid = __nlm_alloc_pid(host);
			new->host = nlm_get_host(host);
			list_add(&new->list, &host->h_lockowners);
			new = NULL;
		}
	}
	spin_unlock(&host->h_lock);
	kfree(new);
	return res;
}