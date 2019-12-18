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
struct hash_entry {int dummy; } ;
struct hash_control {unsigned long size; scalar_t__ deletions; scalar_t__ replacements; scalar_t__ insertions; scalar_t__ string_compares; scalar_t__ hash_compares; scalar_t__ lookups; int /*<<< orphan*/  table; int /*<<< orphan*/  memory; } ;

/* Variables and functions */
 int /*<<< orphan*/  chunksize ; 
 unsigned long get_gas_hash_table_size () ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  obstack_alloc (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  obstack_begin (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct hash_control* xmalloc (int) ; 

struct hash_control *
hash_new (void)
{
  unsigned long size;
  unsigned long alloc;
  struct hash_control *ret;

  size = get_gas_hash_table_size ();

  ret = xmalloc (sizeof *ret);
  obstack_begin (&ret->memory, chunksize);
  alloc = size * sizeof (struct hash_entry *);
  ret->table = obstack_alloc (&ret->memory, alloc);
  memset (ret->table, 0, alloc);
  ret->size = size;

#ifdef HASH_STATISTICS
  ret->lookups = 0;
  ret->hash_compares = 0;
  ret->string_compares = 0;
  ret->insertions = 0;
  ret->replacements = 0;
  ret->deletions = 0;
#endif

  return ret;
}