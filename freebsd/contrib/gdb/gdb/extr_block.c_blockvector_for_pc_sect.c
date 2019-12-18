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
struct symtab {int dummy; } ;
struct blockvector {int dummy; } ;
struct block {int dummy; } ;
struct bfd_section {int dummy; } ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 struct blockvector* BLOCKVECTOR (struct symtab*) ; 
 struct block* BLOCKVECTOR_BLOCK (struct blockvector*,int) ; 
 int BLOCKVECTOR_NBLOCKS (struct blockvector*) ; 
 scalar_t__ BLOCK_END (struct block*) ; 
 scalar_t__ BLOCK_START (struct block*) ; 
 struct symtab* find_pc_sect_symtab (scalar_t__,struct bfd_section*) ; 

struct blockvector *
blockvector_for_pc_sect (CORE_ADDR pc, struct bfd_section *section,
			 int *pindex, struct symtab *symtab)
{
  struct block *b;
  int bot, top, half;
  struct blockvector *bl;

  if (symtab == 0)		/* if no symtab specified by caller */
    {
      /* First search all symtabs for one whose file contains our pc */
      symtab = find_pc_sect_symtab (pc, section);
      if (symtab == 0)
	return 0;
    }

  bl = BLOCKVECTOR (symtab);
  b = BLOCKVECTOR_BLOCK (bl, 0);

  /* Then search that symtab for the smallest block that wins.  */
  /* Use binary search to find the last block that starts before PC.  */

  bot = 0;
  top = BLOCKVECTOR_NBLOCKS (bl);

  while (top - bot > 1)
    {
      half = (top - bot + 1) >> 1;
      b = BLOCKVECTOR_BLOCK (bl, bot + half);
      if (BLOCK_START (b) <= pc)
	bot += half;
      else
	top = bot + half;
    }

  /* Now search backward for a block that ends after PC.  */

  while (bot >= 0)
    {
      b = BLOCKVECTOR_BLOCK (bl, bot);
      if (BLOCK_END (b) > pc)
	{
	  if (pindex)
	    *pindex = bot;
	  return bl;
	}
      bot--;
    }
  return 0;
}