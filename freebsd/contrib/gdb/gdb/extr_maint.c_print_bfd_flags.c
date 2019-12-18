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
typedef  int flagword ;

/* Variables and functions */
 int SEC_ALLOC ; 
 int SEC_CODE ; 
 int SEC_COFF_SHARED_LIBRARY ; 
 int SEC_CONSTRUCTOR ; 
 int SEC_DATA ; 
 int SEC_HAS_CONTENTS ; 
 int SEC_IS_COMMON ; 
 int SEC_LOAD ; 
 int SEC_NEVER_LOAD ; 
 int SEC_READONLY ; 
 int SEC_RELOC ; 
 int SEC_ROM ; 
 int /*<<< orphan*/  printf_filtered (char*) ; 

__attribute__((used)) static void
print_bfd_flags (flagword flags)
{
  if (flags & SEC_ALLOC)
    printf_filtered (" ALLOC");
  if (flags & SEC_LOAD)
    printf_filtered (" LOAD");
  if (flags & SEC_RELOC)
    printf_filtered (" RELOC");
  if (flags & SEC_READONLY)
    printf_filtered (" READONLY");
  if (flags & SEC_CODE)
    printf_filtered (" CODE");
  if (flags & SEC_DATA)
    printf_filtered (" DATA");
  if (flags & SEC_ROM)
    printf_filtered (" ROM");
  if (flags & SEC_CONSTRUCTOR)
    printf_filtered (" CONSTRUCTOR");
  if (flags & SEC_HAS_CONTENTS)
    printf_filtered (" HAS_CONTENTS");
  if (flags & SEC_NEVER_LOAD)
    printf_filtered (" NEVER_LOAD");
  if (flags & SEC_COFF_SHARED_LIBRARY)
    printf_filtered (" COFF_SHARED_LIBRARY");
  if (flags & SEC_IS_COMMON)
    printf_filtered (" IS_COMMON");
}