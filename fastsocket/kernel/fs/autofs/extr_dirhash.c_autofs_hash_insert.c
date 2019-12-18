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
struct autofs_dirhash {struct autofs_dir_ent** h; } ;
struct autofs_dir_ent {struct autofs_dir_ent* next; struct autofs_dir_ent** back; scalar_t__ hash; scalar_t__ dentry; int /*<<< orphan*/  len; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 unsigned int AUTOFS_HASH_SIZE ; 
 int /*<<< orphan*/  DPRINTK (char*) ; 
 int /*<<< orphan*/  autofs_init_usage (struct autofs_dirhash*,struct autofs_dir_ent*) ; 
 int /*<<< orphan*/  autofs_say (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dget (scalar_t__) ; 

void autofs_hash_insert(struct autofs_dirhash *dh, struct autofs_dir_ent *ent)
{
	struct autofs_dir_ent **dhnp;

	DPRINTK(("autofs_hash_insert: hash = 0x%08x, name = ", ent->hash));
	autofs_say(ent->name,ent->len);

	autofs_init_usage(dh,ent);
	if (ent->dentry)
		dget(ent->dentry);

	dhnp = &dh->h[(unsigned) ent->hash % AUTOFS_HASH_SIZE];
	ent->next = *dhnp;
	ent->back = dhnp;
	*dhnp = ent;
	if ( ent->next )
		ent->next->back = &(ent->next);
}