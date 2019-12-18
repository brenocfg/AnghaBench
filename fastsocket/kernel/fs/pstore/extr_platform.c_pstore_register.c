#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pstore_info {int /*<<< orphan*/  name; int /*<<< orphan*/  read_mutex; struct module* owner; } ;
struct module {int dummy; } ;
struct TYPE_3__ {scalar_t__ expires; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int EPERM ; 
 scalar_t__ PSTORE_INTERVAL ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 scalar_t__ backend ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  kmsg_dump_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 struct pstore_info* psinfo ; 
 int /*<<< orphan*/  pstore_dumper ; 
 int /*<<< orphan*/  pstore_get_records (int /*<<< orphan*/ ) ; 
 scalar_t__ pstore_is_mounted () ; 
 int /*<<< orphan*/  pstore_lock ; 
 TYPE_1__ pstore_timer ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  try_module_get (struct module*) ; 

int pstore_register(struct pstore_info *psi)
{
	struct module *owner = psi->owner;

	if (backend && strcmp(backend, psi->name))
		return -EPERM;

	spin_lock(&pstore_lock);
	if (psinfo) {
		spin_unlock(&pstore_lock);
		return -EBUSY;
	}

	psinfo = psi;
	mutex_init(&psinfo->read_mutex);
	spin_unlock(&pstore_lock);

	if (owner && !try_module_get(owner)) {
		psinfo = NULL;
		return -EINVAL;
	}

	if (pstore_is_mounted())
		pstore_get_records(0);

	kmsg_dump_register(&pstore_dumper);

	pstore_timer.expires = jiffies + PSTORE_INTERVAL;
	add_timer(&pstore_timer);

	pr_info("pstore: Registered %s as persistent store backend\n",
		psi->name);

	return 0;
}