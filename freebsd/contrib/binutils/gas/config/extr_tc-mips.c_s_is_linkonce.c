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
typedef  scalar_t__ segT ;
typedef  int /*<<< orphan*/  bfd_boolean ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int SEC_LINK_ONCE ; 
 scalar_t__ S_GET_SEGMENT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_IS_LOCAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int bfd_get_section_flags (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  segment_name (scalar_t__) ; 
 int /*<<< orphan*/  stdoutput ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static bfd_boolean
s_is_linkonce (symbolS *sym, segT from_seg)
{
  bfd_boolean linkonce = FALSE;
  segT symseg = S_GET_SEGMENT (sym);

  if (symseg != from_seg && !S_IS_LOCAL (sym))
    {
      if ((bfd_get_section_flags (stdoutput, symseg) & SEC_LINK_ONCE))
	linkonce = TRUE;
#ifdef OBJ_ELF
      /* The GNU toolchain uses an extension for ELF: a section
	 beginning with the magic string .gnu.linkonce is a
	 linkonce section.  */
      if (strncmp (segment_name (symseg), ".gnu.linkonce",
		   sizeof ".gnu.linkonce" - 1) == 0)
	linkonce = TRUE;
#endif
    }
  return linkonce;
}