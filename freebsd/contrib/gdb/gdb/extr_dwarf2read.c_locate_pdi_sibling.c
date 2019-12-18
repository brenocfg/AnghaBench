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
struct partial_die_info {char* sibling; scalar_t__ tag; int /*<<< orphan*/  has_children; } ;
struct dwarf2_cu {int dummy; } ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 char* read_partial_die (struct partial_die_info*,int /*<<< orphan*/ *,char*,struct dwarf2_cu*) ; 

__attribute__((used)) static char *
locate_pdi_sibling (struct partial_die_info *orig_pdi, char *info_ptr,
		    bfd *abfd, struct dwarf2_cu *cu)
{
  /* Do we know the sibling already?  */
  
  if (orig_pdi->sibling)
    return orig_pdi->sibling;

  /* Are there any children to deal with?  */

  if (!orig_pdi->has_children)
    return info_ptr;

  /* Okay, we don't know the sibling, but we have children that we
     want to skip.  So read children until we run into one without a
     tag; return whatever follows it.  */

  while (1)
    {
      struct partial_die_info pdi;
      
      info_ptr = read_partial_die (&pdi, abfd, info_ptr, cu);

      if (pdi.tag == 0)
	return info_ptr;
      else
	info_ptr = locate_pdi_sibling (&pdi, info_ptr, abfd, cu);
    }
}