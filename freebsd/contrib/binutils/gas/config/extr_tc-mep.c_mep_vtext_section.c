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
typedef  scalar_t__ segT ;
typedef  int flagword ;

/* Variables and functions */
 int SEC_ALLOC ; 
 int SEC_CODE ; 
 int SEC_LOAD ; 
 int SEC_MEP_VLIW ; 
 int SEC_READONLY ; 
 int SEC_RELOC ; 
 int /*<<< orphan*/  VTEXT_SECTION_NAME ; 
 int bfd_applicable_section_flags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_set_section_flags (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  stdoutput ; 
 scalar_t__ subseg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static segT
mep_vtext_section (void)
{
  static segT vtext_section;

  if (! vtext_section)
    {
      flagword applicable = bfd_applicable_section_flags (stdoutput);
      vtext_section = subseg_new (VTEXT_SECTION_NAME, 0);
      bfd_set_section_flags (stdoutput, vtext_section,
			     applicable & (SEC_ALLOC | SEC_LOAD | SEC_RELOC
					   | SEC_CODE | SEC_READONLY
					   | SEC_MEP_VLIW));
    }

  return vtext_section;
}