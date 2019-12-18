#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ bfd_size_type ;
struct TYPE_2__ {unsigned int split_by_reloc; scalar_t__ split_by_file; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ bfd_error_no_error ; 
 int /*<<< orphan*/  bfd_final_link (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ bfd_get_error () ; 
 int /*<<< orphan*/  bfd_set_error (scalar_t__) ; 
 int /*<<< orphan*/  build_link_order ; 
 TYPE_1__ config ; 
 int /*<<< orphan*/  einfo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lang_for_each_statement (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link_info ; 
 int /*<<< orphan*/  output_bfd ; 
 int /*<<< orphan*/  split_sections (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xexit (int) ; 

void
ldwrite (void)
{
  /* Reset error indicator, which can typically something like invalid
     format from opening up the .o files.  */
  bfd_set_error (bfd_error_no_error);
  lang_for_each_statement (build_link_order);

  if (config.split_by_reloc != (unsigned) -1
      || config.split_by_file != (bfd_size_type) -1)
    split_sections (output_bfd, &link_info);
  if (!bfd_final_link (output_bfd, &link_info))
    {
      /* If there was an error recorded, print it out.  Otherwise assume
	 an appropriate error message like unknown symbol was printed
	 out.  */

      if (bfd_get_error () != bfd_error_no_error)
	einfo (_("%F%P: final link failed: %E\n"));
      else
	xexit (1);
    }
}