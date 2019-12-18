#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* string_section_name; int /*<<< orphan*/  string_offset; int /*<<< orphan*/  section_name; } ;
typedef  TYPE_1__ stab_section_names ;
typedef  int /*<<< orphan*/  bfd_byte ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_5__ {char* name; } ;
typedef  TYPE_2__ asection ;

/* Variables and functions */
 scalar_t__ ISDIGIT (char) ; 
 int /*<<< orphan*/  print_section_stabs (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * read_section_stabs (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stab_size ; 
 int /*<<< orphan*/ * stabs ; 
 int /*<<< orphan*/  stabstr_size ; 
 int strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/ * strtab ; 

__attribute__((used)) static void
find_stabs_section (bfd *abfd, asection *section, void *names)
{
  int len;
  stab_section_names * sought = (stab_section_names *) names;

  /* Check for section names for which stabsect_name is a prefix, to
     handle .stab.N, etc.  */
  len = strlen (sought->section_name);

  /* If the prefix matches, and the files section name ends with a
     nul or a digit, then we match.  I.e., we want either an exact
     match or a section followed by a number.  */
  if (strncmp (sought->section_name, section->name, len) == 0
      && (section->name[len] == 0
	  || (section->name[len] == '.' && ISDIGIT (section->name[len + 1]))))
    {
      if (strtab == NULL)
	strtab = read_section_stabs (abfd, sought->string_section_name,
				     &stabstr_size);
      
      if (strtab)
	{
	  stabs = (bfd_byte *) read_section_stabs (abfd, section->name,
						   &stab_size);
	  if (stabs)
	    print_section_stabs (abfd, section->name, &sought->string_offset);
	}
    }
}