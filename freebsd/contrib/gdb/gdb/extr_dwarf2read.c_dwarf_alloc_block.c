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
struct dwarf_block {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dwarf2_tmp_obstack ; 
 scalar_t__ obstack_alloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static struct dwarf_block *
dwarf_alloc_block (void)
{
  struct dwarf_block *blk;

  blk = (struct dwarf_block *)
    obstack_alloc (&dwarf2_tmp_obstack, sizeof (struct dwarf_block));
  return (blk);
}