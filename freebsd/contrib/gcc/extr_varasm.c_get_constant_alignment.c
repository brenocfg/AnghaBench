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
typedef  int /*<<< orphan*/  tree ;

/* Variables and functions */
 unsigned int CONSTANT_ALIGNMENT (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 unsigned int TYPE_ALIGN (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int
get_constant_alignment (tree exp)
{
  unsigned int align;

  align = TYPE_ALIGN (TREE_TYPE (exp));
#ifdef CONSTANT_ALIGNMENT
  align = CONSTANT_ALIGNMENT (exp, align);
#endif
  return align;
}