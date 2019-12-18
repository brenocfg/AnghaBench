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
struct proc_dir_entry {char* name; int namelen; int /*<<< orphan*/  pde_openers; int /*<<< orphan*/ * pde_unload_completion; int /*<<< orphan*/  pde_unload_lock; scalar_t__ pde_users; int /*<<< orphan*/  count; int /*<<< orphan*/  nlink; int /*<<< orphan*/  mode; } ;
typedef  int /*<<< orphan*/  nlink_t ;
typedef  int /*<<< orphan*/  mode_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 struct proc_dir_entry* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  memset (struct proc_dir_entry*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 scalar_t__ strchr (char const*,char) ; 
 int strlen (char const*) ; 
 scalar_t__ xlate_proc_name (char const*,struct proc_dir_entry**,char const**) ; 

__attribute__((used)) static struct proc_dir_entry *__proc_create(struct proc_dir_entry **parent,
					  const char *name,
					  mode_t mode,
					  nlink_t nlink)
{
	struct proc_dir_entry *ent = NULL;
	const char *fn = name;
	int len;

	/* make sure name is valid */
	if (!name || !strlen(name)) goto out;

	if (xlate_proc_name(name, parent, &fn) != 0)
		goto out;

	/* At this point there must not be any '/' characters beyond *fn */
	if (strchr(fn, '/'))
		goto out;

	len = strlen(fn);

	ent = kmalloc(sizeof(struct proc_dir_entry) + len + 1, GFP_KERNEL);
	if (!ent) goto out;

	memset(ent, 0, sizeof(struct proc_dir_entry));
	memcpy(((char *) ent) + sizeof(struct proc_dir_entry), fn, len + 1);
	ent->name = ((char *) ent) + sizeof(*ent);
	ent->namelen = len;
	ent->mode = mode;
	ent->nlink = nlink;
	atomic_set(&ent->count, 1);
	ent->pde_users = 0;
	spin_lock_init(&ent->pde_unload_lock);
	ent->pde_unload_completion = NULL;
	INIT_LIST_HEAD(&ent->pde_openers);
 out:
	return ent;
}