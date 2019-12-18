#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {unsigned long hash; scalar_t__ next; } ;
struct TYPE_7__ {int constraint; int /*<<< orphan*/  name; } ;
struct TYPE_5__ {TYPE_3__ output_section_statement; } ;
struct out_section_hash_entry {TYPE_2__ root; TYPE_1__ s; } ;
typedef  TYPE_3__ lang_output_section_statement_type ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ bfd_hash_lookup (int /*<<< orphan*/ *,char const* const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  output_section_statement_table ; 
 scalar_t__ strcmp (char const* const,int /*<<< orphan*/ ) ; 

lang_output_section_statement_type *
lang_output_section_find (const char *const name)
{
  struct out_section_hash_entry *entry;
  unsigned long hash;

  entry = ((struct out_section_hash_entry *)
	   bfd_hash_lookup (&output_section_statement_table, name,
			    FALSE, FALSE));
  if (entry == NULL)
    return NULL;

  hash = entry->root.hash;
  do
    {
      if (entry->s.output_section_statement.constraint != -1)
	return &entry->s.output_section_statement;
      entry = (struct out_section_hash_entry *) entry->root.next;
    }
  while (entry != NULL
	 && entry->root.hash == hash
	 && strcmp (name, entry->s.output_section_statement.name) == 0);

  return NULL;
}