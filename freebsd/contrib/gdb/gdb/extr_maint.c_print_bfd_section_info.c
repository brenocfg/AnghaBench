#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  flagword ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_7__ {int /*<<< orphan*/  filepos; } ;
typedef  TYPE_1__ asection ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  bfd_get_section_flags (int /*<<< orphan*/ *,TYPE_1__*) ; 
 char* bfd_section_name (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ bfd_section_size (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ bfd_section_vma (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  maint_print_section_info (char const*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ match_bfd_flags (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ match_substring (char*,char const*) ; 

__attribute__((used)) static void
print_bfd_section_info (bfd *abfd, 
			asection *asect, 
			void *arg)
{
  flagword flags = bfd_get_section_flags (abfd, asect);
  const char *name = bfd_section_name (abfd, asect);

  if (arg == NULL || *((char *) arg) == '\0'
      || match_substring ((char *) arg, name)
      || match_bfd_flags ((char *) arg, flags))
    {
      CORE_ADDR addr, endaddr;

      addr = bfd_section_vma (abfd, asect);
      endaddr = addr + bfd_section_size (abfd, asect);
      maint_print_section_info (name, flags, addr, endaddr, asect->filepos);
    }
}