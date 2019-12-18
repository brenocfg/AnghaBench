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
struct line_header {struct line_header* include_dirs; struct line_header* file_names; struct line_header* standard_opcode_lengths; } ;

/* Variables and functions */
 int /*<<< orphan*/  xfree (struct line_header*) ; 

__attribute__((used)) static void
free_line_header (struct line_header *lh)
{
  if (lh->standard_opcode_lengths)
    xfree (lh->standard_opcode_lengths);

  /* Remember that all the lh->file_names[i].name pointers are
     pointers into debug_line_buffer, and don't need to be freed.  */
  if (lh->file_names)
    xfree (lh->file_names);

  /* Similarly for the include directory names.  */
  if (lh->include_dirs)
    xfree (lh->include_dirs);

  xfree (lh);
}