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
typedef  int /*<<< orphan*/  relax_substateT ;
typedef  int /*<<< orphan*/  offsetT ;
typedef  int addressT ;

/* Variables and functions */
 int abs_section_offset ; 
 scalar_t__ absolute_section ; 
 char* frag_var (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ now_seg ; 
 int /*<<< orphan*/  rs_align ; 

void
frag_align (int alignment, int fill_character, int max)
{
  if (now_seg == absolute_section)
    {
      addressT new_off;
      addressT mask;

      mask = (~(addressT) 0) << alignment;
      new_off = (abs_section_offset + ~mask) & mask;
      if (max == 0 || new_off - abs_section_offset <= (addressT) max)
	abs_section_offset = new_off;
    }
  else
    {
      char *p;

      p = frag_var (rs_align, 1, 1, (relax_substateT) max,
		    (symbolS *) 0, (offsetT) alignment, (char *) 0);
      *p = fill_character;
    }
}