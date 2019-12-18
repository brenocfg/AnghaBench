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
struct symbol {int dummy; } ;
struct block {int dummy; } ;
struct bfd_section {int dummy; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 struct block* block_for_pc_sect (int /*<<< orphan*/ ,struct bfd_section*) ; 
 struct symbol* block_function (struct block*) ; 

struct symbol *
find_pc_sect_function (CORE_ADDR pc, struct bfd_section *section)
{
  struct block *b = block_for_pc_sect (pc, section);
  if (b == 0)
    return 0;
  return block_function (b);
}