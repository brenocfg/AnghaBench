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
struct strtab_hash_entry {int dummy; } ;
struct bfd_strtab_hash {int /*<<< orphan*/  xcoff; int /*<<< orphan*/ * last; int /*<<< orphan*/ * first; scalar_t__ size; int /*<<< orphan*/  table; } ;
typedef  int bfd_size_type ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  bfd_hash_table_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct bfd_strtab_hash* bfd_malloc (int) ; 
 int /*<<< orphan*/  free (struct bfd_strtab_hash*) ; 
 int /*<<< orphan*/  strtab_hash_newfunc ; 

struct bfd_strtab_hash *
_bfd_stringtab_init (void)
{
  struct bfd_strtab_hash *table;
  bfd_size_type amt = sizeof (* table);

  table = bfd_malloc (amt);
  if (table == NULL)
    return NULL;

  if (!bfd_hash_table_init (&table->table, strtab_hash_newfunc,
			    sizeof (struct strtab_hash_entry)))
    {
      free (table);
      return NULL;
    }

  table->size = 0;
  table->first = NULL;
  table->last = NULL;
  table->xcoff = FALSE;

  return table;
}