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

/* Variables and functions */
 int SEC_HAS_CONTENTS ; 
 int SEC_READONLY ; 
 scalar_t__ arcext_section ; 
 int /*<<< orphan*/  bfd_set_section_flags (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  stdoutput ; 
 scalar_t__ subseg_new (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  subseg_set (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
arc_set_ext_seg (void)
{
  if (!arcext_section)
    {
      arcext_section = subseg_new (".arcextmap", 0);
      bfd_set_section_flags (stdoutput, arcext_section,
			     SEC_READONLY | SEC_HAS_CONTENTS);
    }
  else
    subseg_set (arcext_section, 0);
  return 1;
}