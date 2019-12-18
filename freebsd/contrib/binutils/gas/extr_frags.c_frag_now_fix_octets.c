#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  char* addressT ;
struct TYPE_4__ {int fr_literal; } ;
struct TYPE_3__ {int /*<<< orphan*/  frch_obstack; } ;

/* Variables and functions */
 char* abs_section_offset ; 
 scalar_t__ absolute_section ; 
 TYPE_2__* frag_now ; 
 TYPE_1__* frchain_now ; 
 scalar_t__ now_seg ; 
 scalar_t__ obstack_next_free (int /*<<< orphan*/ *) ; 

addressT
frag_now_fix_octets (void)
{
  if (now_seg == absolute_section)
    return abs_section_offset;

  return ((char *) obstack_next_free (&frchain_now->frch_obstack)
	  - frag_now->fr_literal);
}