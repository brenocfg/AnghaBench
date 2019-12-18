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
struct df_reg_info {unsigned int begin; int n_refs; struct df_ref* reg_chain; } ;
struct df_ref_info {unsigned int regs_inited; int refs_organized; int refs_size; int bitmap_size; int add_refs_inline; struct df_ref** refs; struct df_reg_info** regs; } ;
struct df_ref {int dummy; } ;
typedef  int /*<<< orphan*/  DF_REF_ID ;

/* Variables and functions */
 int /*<<< orphan*/  DF_REF_NEXT_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  df_grow_ref_info (struct df_ref_info*,int) ; 

void 
df_reorganize_refs (struct df_ref_info *ref_info)
{
  unsigned int m = ref_info->regs_inited;
  unsigned int regno;
  unsigned int offset = 0;
  unsigned int size = 0;

  if (ref_info->refs_organized)
    return;

  if (ref_info->refs_size < ref_info->bitmap_size)
    {  
      int new_size = ref_info->bitmap_size + ref_info->bitmap_size / 4;
      df_grow_ref_info (ref_info, new_size);
    }

  for (regno = 0; regno < m; regno++)
    {
      struct df_reg_info *reg_info = ref_info->regs[regno];
      int count = 0;
      if (reg_info)
	{
	  struct df_ref *ref = reg_info->reg_chain;
	  reg_info->begin = offset;
	  while (ref) 
	    {
	      ref_info->refs[offset] = ref;
	      DF_REF_ID (ref) = offset++;
	      ref = DF_REF_NEXT_REG (ref);
	      count++;
	      size++;
	    }
	  reg_info->n_refs = count;
	}
    }

  /* The bitmap size is not decremented when refs are deleted.  So
     reset it now that we have squished out all of the empty
     slots.  */
  ref_info->bitmap_size = size;
  ref_info->refs_organized = true;
  ref_info->add_refs_inline = true;
}