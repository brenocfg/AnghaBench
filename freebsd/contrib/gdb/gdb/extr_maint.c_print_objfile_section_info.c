#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct obj_section {TYPE_1__* the_bfd_section; int /*<<< orphan*/  endaddr; int /*<<< orphan*/  addr; } ;
typedef  int /*<<< orphan*/  flagword ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_3__ {int /*<<< orphan*/  filepos; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfd_get_section_flags (int /*<<< orphan*/ *,TYPE_1__*) ; 
 char* bfd_section_name (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  maint_print_section_info (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ match_bfd_flags (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ match_substring (char*,char const*) ; 

__attribute__((used)) static void
print_objfile_section_info (bfd *abfd, 
			    struct obj_section *asect, 
			    char *string)
{
  flagword flags = bfd_get_section_flags (abfd, asect->the_bfd_section);
  const char *name = bfd_section_name (abfd, asect->the_bfd_section);

  if (string == NULL || *string == '\0'
      || match_substring (string, name)
      || match_bfd_flags (string, flags))
    {
      maint_print_section_info (name, flags, asect->addr, asect->endaddr, 
			  asect->the_bfd_section->filepos);
    }
}