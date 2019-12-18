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
typedef  int bfd_boolean ;
struct TYPE_3__ {int /*<<< orphan*/  xvec; } ;
typedef  TYPE_1__ bfd ;

/* Variables and functions */
 scalar_t__ CONST_STRNEQ (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ELF_STRING_ia64_unwind ; 
 int /*<<< orphan*/  ELF_STRING_ia64_unwind_hdr ; 
 int /*<<< orphan*/  ELF_STRING_ia64_unwind_info ; 
 int /*<<< orphan*/  ELF_STRING_ia64_unwind_once ; 
 int FALSE ; 
 scalar_t__ elfNN_ia64_hpux_vec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bfd_boolean
is_unwind_section_name (bfd *abfd, const char *name)
{
  if (elfNN_ia64_hpux_vec (abfd->xvec)
      && !strcmp (name, ELF_STRING_ia64_unwind_hdr))
    return FALSE;

  return ((CONST_STRNEQ (name, ELF_STRING_ia64_unwind)
	   && ! CONST_STRNEQ (name, ELF_STRING_ia64_unwind_info))
	  || CONST_STRNEQ (name, ELF_STRING_ia64_unwind_once));
}