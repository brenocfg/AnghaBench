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
struct objalloc {int dummy; } ;
struct bfd_hash_table {unsigned int size; unsigned int entsize; struct bfd_hash_entry* (* newfunc ) (struct bfd_hash_entry*,struct bfd_hash_table*,char const*) ;scalar_t__ frozen; scalar_t__ count; int /*<<< orphan*/ * table; int /*<<< orphan*/ * memory; } ;
struct bfd_hash_entry {int dummy; } ;
typedef  int /*<<< orphan*/  bfd_boolean ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bfd_error_no_memory ; 
 int /*<<< orphan*/  bfd_set_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/ * objalloc_alloc (struct objalloc*,unsigned int) ; 
 scalar_t__ objalloc_create () ; 

bfd_boolean
bfd_hash_table_init_n (struct bfd_hash_table *table,
		       struct bfd_hash_entry *(*newfunc) (struct bfd_hash_entry *,
							  struct bfd_hash_table *,
							  const char *),
		       unsigned int entsize,
		       unsigned int size)
{
  unsigned int alloc;

  alloc = size * sizeof (struct bfd_hash_entry *);

  table->memory = (void *) objalloc_create ();
  if (table->memory == NULL)
    {
      bfd_set_error (bfd_error_no_memory);
      return FALSE;
    }
  table->table = objalloc_alloc ((struct objalloc *) table->memory, alloc);
  if (table->table == NULL)
    {
      bfd_set_error (bfd_error_no_memory);
      return FALSE;
    }
  memset ((void *) table->table, 0, alloc);
  table->size = size;
  table->entsize = entsize;
  table->count = 0;
  table->frozen = 0;
  table->newfunc = newfunc;
  return TRUE;
}