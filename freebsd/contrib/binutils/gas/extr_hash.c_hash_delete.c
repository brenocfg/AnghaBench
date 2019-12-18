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
struct hash_entry {int /*<<< orphan*/ * data; struct hash_entry* next; } ;
struct hash_control {int /*<<< orphan*/  deletions; } ;
typedef  int /*<<< orphan*/ * PTR ;

/* Variables and functions */
 int /*<<< orphan*/  abort () ; 
 struct hash_entry* hash_lookup (struct hash_control*,char const*,int /*<<< orphan*/ ,struct hash_entry***,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

PTR
hash_delete (struct hash_control *table, const char *key)
{
  struct hash_entry *p;
  struct hash_entry **list;

  p = hash_lookup (table, key, strlen (key), &list, NULL);
  if (p == NULL)
    return NULL;

  if (p != *list)
    abort ();

#ifdef HASH_STATISTICS
  ++table->deletions;
#endif

  *list = p->next;

  /* Note that we never reclaim the memory for this entry.  If gas
     ever starts deleting hash table entries in a big way, this will
     have to change.  */

  return p->data;
}