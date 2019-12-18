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
typedef  int /*<<< orphan*/  symbolS ;
typedef  int /*<<< orphan*/  segT ;

/* Variables and functions */
 int SEC_ALLOC ; 
 int SEC_DATA ; 
 int SEC_LOAD ; 
 int SEC_READONLY ; 
 int SEC_RELOC ; 
 int /*<<< orphan*/  S_CLEAR_EXTERNAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_set_section_alignment (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bfd_set_section_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  now_seg ; 
 int now_subseg ; 
 int /*<<< orphan*/ * section_symbol (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdoutput ; 
 int /*<<< orphan*/  subseg_new (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  subseg_set (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
create_literal_section (const char *name,
			segT *secp,
			symbolS **symp)
{
  segT current_section = now_seg;
  int current_subsec = now_subseg;
  segT new_sec;

  *secp = new_sec = subseg_new (name, 0);
  subseg_set (current_section, current_subsec);
  bfd_set_section_alignment (stdoutput, new_sec, 4);
  bfd_set_section_flags (stdoutput, new_sec,
			 SEC_RELOC | SEC_ALLOC | SEC_LOAD | SEC_READONLY
			 | SEC_DATA);

  S_CLEAR_EXTERNAL (*symp = section_symbol (new_sec));
}