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

/* Variables and functions */
 scalar_t__ absolute_section ; 
 unsigned int bfd_get_section_alignment (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bfd_set_section_alignment (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  stdoutput ; 

void
record_alignment (/* Segment to which alignment pertains.  */
		  segT seg,
		  /* Alignment, as a power of 2 (e.g., 1 => 2-byte
		     boundary, 2 => 4-byte boundary, etc.)  */
		  int align)
{
  if (seg == absolute_section)
    return;

  if ((unsigned int) align > bfd_get_section_alignment (stdoutput, seg))
    (void) bfd_set_section_alignment (stdoutput, seg, align);
}