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
struct blockvector {int dummy; } ;
struct block {int dummy; } ;
struct bfd_section {int dummy; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 struct block* BLOCKVECTOR_BLOCK (struct blockvector*,int) ; 
 struct blockvector* blockvector_for_pc_sect (int /*<<< orphan*/ ,struct bfd_section*,int*,int /*<<< orphan*/ *) ; 

struct block *
block_for_pc_sect (CORE_ADDR pc, struct bfd_section *section)
{
  struct blockvector *bl;
  int index;

  bl = blockvector_for_pc_sect (pc, section, &index, NULL);
  if (bl)
    return BLOCKVECTOR_BLOCK (bl, index);
  return 0;
}