#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  head; } ;
struct TYPE_8__ {scalar_t__ name; TYPE_1__ children; TYPE_3__* bfd_section; } ;
typedef  TYPE_2__ lang_output_section_statement_type ;
struct TYPE_9__ {scalar_t__ vma; scalar_t__ lma; int /*<<< orphan*/  size; } ;
typedef  TYPE_3__ asection ;

/* Variables and functions */
 int SECTION_NAME_MAP_LENGTH ; 
 char* _ (char*) ; 
 TYPE_2__* abs_output_section ; 
 int /*<<< orphan*/  minfo (char*,scalar_t__,...) ; 
 scalar_t__ print_dot ; 
 int /*<<< orphan*/  print_nl () ; 
 int /*<<< orphan*/  print_space () ; 
 int /*<<< orphan*/  print_statement_list (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int strlen (scalar_t__) ; 

__attribute__((used)) static void
print_output_section_statement
  (lang_output_section_statement_type *output_section_statement)
{
  asection *section = output_section_statement->bfd_section;
  int len;

  if (output_section_statement != abs_output_section)
    {
      minfo ("\n%s", output_section_statement->name);

      if (section != NULL)
	{
	  print_dot = section->vma;

	  len = strlen (output_section_statement->name);
	  if (len >= SECTION_NAME_MAP_LENGTH - 1)
	    {
	      print_nl ();
	      len = 0;
	    }
	  while (len < SECTION_NAME_MAP_LENGTH)
	    {
	      print_space ();
	      ++len;
	    }

	  minfo ("0x%V %W", section->vma, section->size);

	  if (section->vma != section->lma)
	    minfo (_(" load address 0x%V"), section->lma);
	}

      print_nl ();
    }

  print_statement_list (output_section_statement->children.head,
			output_section_statement);
}