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
struct TYPE_7__ {char* name; int constraint; } ;
struct TYPE_6__ {TYPE_3__ output_section_statement; } ;
struct TYPE_5__ {unsigned long hash; struct TYPE_5__* next; } ;
struct out_section_hash_entry {TYPE_2__ s; TYPE_1__ root; } ;
typedef  TYPE_3__ lang_output_section_statement_type ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int SPECIAL ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ bfd_hash_lookup (int /*<<< orphan*/ *,char const* const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  einfo (int /*<<< orphan*/ ,char const* const) ; 
 scalar_t__ output_section_statement_newfunc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const* const) ; 
 int /*<<< orphan*/  output_section_statement_table ; 
 scalar_t__ strcmp (char const* const,char*) ; 

__attribute__((used)) static lang_output_section_statement_type *
lang_output_section_statement_lookup_1 (const char *const name, int constraint)
{
  struct out_section_hash_entry *entry;
  struct out_section_hash_entry *last_ent;
  unsigned long hash;

  entry = ((struct out_section_hash_entry *)
	   bfd_hash_lookup (&output_section_statement_table, name,
			    TRUE, FALSE));
  if (entry == NULL)
    {
      einfo (_("%P%F: failed creating section `%s': %E\n"), name);
      return NULL;
    }

  if (entry->s.output_section_statement.name != NULL)
    {
      /* We have a section of this name, but it might not have the correct
	 constraint.  */
      hash = entry->root.hash;
      do
	{
	  if (entry->s.output_section_statement.constraint != -1
	      && (constraint == 0
		  || (constraint == entry->s.output_section_statement.constraint
		      && constraint != SPECIAL)))
	    return &entry->s.output_section_statement;
	  last_ent = entry;
	  entry = (struct out_section_hash_entry *) entry->root.next;
	}
      while (entry != NULL
	     && entry->root.hash == hash
	     && strcmp (name, entry->s.output_section_statement.name) == 0);

      entry
	= ((struct out_section_hash_entry *)
	   output_section_statement_newfunc (NULL,
					     &output_section_statement_table,
					     name));
      if (entry == NULL)
	{
	  einfo (_("%P%F: failed creating section `%s': %E\n"), name);
	  return NULL;
	}
      entry->root = last_ent->root;
      last_ent->root.next = &entry->root;
    }

  entry->s.output_section_statement.name = name;
  entry->s.output_section_statement.constraint = constraint;
  return &entry->s.output_section_statement;
}