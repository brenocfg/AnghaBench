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
struct cfil_hash_entry {int dummy; } ;
struct cfil_db {struct cfil_hash_entry* cfdb_only_entry; int /*<<< orphan*/  cfdb_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (struct cfil_hash_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfentry_link ; 
 int /*<<< orphan*/  cfil_hash_entry_zone ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ ,struct cfil_hash_entry*) ; 

void
cfil_db_delete_entry(struct cfil_db *db, struct cfil_hash_entry *hash_entry)
{
    if (hash_entry == NULL)
        return;

    LIST_REMOVE(hash_entry, cfentry_link);
    zfree(cfil_hash_entry_zone, hash_entry);
    db->cfdb_count--;
    if (db->cfdb_only_entry == hash_entry)
        db->cfdb_only_entry = NULL;
}