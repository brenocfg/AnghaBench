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
typedef  int /*<<< orphan*/  tree ;
struct TYPE_2__ {unsigned int stack_alignment_needed; } ;

/* Variables and functions */
 unsigned int BITS_PER_UNIT ; 
 unsigned int DECL_ALIGN (int /*<<< orphan*/ ) ; 
 unsigned int LOCAL_ALIGNMENT (int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int PREFERRED_STACK_BOUNDARY ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 TYPE_1__* cfun ; 

__attribute__((used)) static unsigned int
get_decl_align_unit (tree decl)
{
  unsigned int align;

  align = DECL_ALIGN (decl);
  align = LOCAL_ALIGNMENT (TREE_TYPE (decl), align);
  if (align > PREFERRED_STACK_BOUNDARY)
    align = PREFERRED_STACK_BOUNDARY;
  if (cfun->stack_alignment_needed < align)
    cfun->stack_alignment_needed = align;

  return align / BITS_PER_UNIT;
}