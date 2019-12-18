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
typedef  int /*<<< orphan*/  file_ptr ;
typedef  int /*<<< orphan*/  bfd_size_type ;
typedef  int /*<<< orphan*/  bfd_byte ;
typedef  int /*<<< orphan*/  bfd_boolean ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ bfd_section_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_set_section_contents (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  data_section ; 
 int /*<<< orphan*/  stdoutput ; 
 int /*<<< orphan*/  text_section ; 

void
obj_aout_frob_file_before_fix (void)
{
  /* Relocation processing may require knowing the VMAs of the sections.
     Since writing to a section will cause the BFD back end to compute the
     VMAs, fake it out here....  */
  bfd_byte b = 0;
  bfd_boolean x = TRUE;
  if (bfd_section_size (stdoutput, text_section) != 0)
    x = bfd_set_section_contents (stdoutput, text_section, &b, (file_ptr) 0,
				  (bfd_size_type) 1);
  else if (bfd_section_size (stdoutput, data_section) != 0)
    x = bfd_set_section_contents (stdoutput, data_section, &b, (file_ptr) 0,
				  (bfd_size_type) 1);

  assert (x);
}