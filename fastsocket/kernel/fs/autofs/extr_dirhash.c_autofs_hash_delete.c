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
struct autofs_dir_ent {struct autofs_dir_ent* name; scalar_t__ dentry; TYPE_1__** back; TYPE_1__* next; } ;
struct TYPE_2__ {struct TYPE_2__** back; } ;

/* Variables and functions */
 int /*<<< orphan*/  autofs_delete_usage (struct autofs_dir_ent*) ; 
 int /*<<< orphan*/  dput (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct autofs_dir_ent*) ; 

void autofs_hash_delete(struct autofs_dir_ent *ent)
{
	*(ent->back) = ent->next;
	if ( ent->next )
		ent->next->back = ent->back;

	autofs_delete_usage(ent);

	if ( ent->dentry )
		dput(ent->dentry);
	kfree(ent->name);
	kfree(ent);
}