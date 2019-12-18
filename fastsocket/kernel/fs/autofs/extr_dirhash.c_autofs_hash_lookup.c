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
struct qstr {scalar_t__ hash; scalar_t__ len; int /*<<< orphan*/  name; } ;
struct autofs_dirhash {struct autofs_dir_ent** h; } ;
struct autofs_dir_ent {scalar_t__ hash; scalar_t__ len; int /*<<< orphan*/  name; struct autofs_dir_ent* next; } ;

/* Variables and functions */
 unsigned int AUTOFS_HASH_SIZE ; 
 int /*<<< orphan*/  DPRINTK (char*) ; 
 int /*<<< orphan*/  autofs_say (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

struct autofs_dir_ent *autofs_hash_lookup(const struct autofs_dirhash *dh, struct qstr *name)
{
	struct autofs_dir_ent *dhn;

	DPRINTK(("autofs_hash_lookup: hash = 0x%08x, name = ", name->hash));
	autofs_say(name->name,name->len);

	for ( dhn = dh->h[(unsigned) name->hash % AUTOFS_HASH_SIZE] ; dhn ; dhn = dhn->next ) {
		if ( name->hash == dhn->hash &&
		     name->len == dhn->len &&
		     !memcmp(name->name, dhn->name, name->len) )
			break;
	}

	return dhn;
}