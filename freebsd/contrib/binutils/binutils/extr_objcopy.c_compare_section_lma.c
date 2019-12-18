#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int flagword ;
struct TYPE_3__ {int flags; scalar_t__ lma; } ;
typedef  TYPE_1__ asection ;

/* Variables and functions */
 int SEC_HAS_CONTENTS ; 
 int SEC_LOAD ; 
 scalar_t__ bfd_get_section_size (TYPE_1__ const* const) ; 

__attribute__((used)) static int
compare_section_lma (const void *arg1, const void *arg2)
{
  const asection *const *sec1 = arg1;
  const asection *const *sec2 = arg2;
  flagword flags1, flags2;

  /* Sort non loadable sections to the front.  */
  flags1 = (*sec1)->flags;
  flags2 = (*sec2)->flags;
  if ((flags1 & SEC_HAS_CONTENTS) == 0
      || (flags1 & SEC_LOAD) == 0)
    {
      if ((flags2 & SEC_HAS_CONTENTS) != 0
	  && (flags2 & SEC_LOAD) != 0)
	return -1;
    }
  else
    {
      if ((flags2 & SEC_HAS_CONTENTS) == 0
	  || (flags2 & SEC_LOAD) == 0)
	return 1;
    }

  /* Sort sections by LMA.  */
  if ((*sec1)->lma > (*sec2)->lma)
    return 1;
  else if ((*sec1)->lma < (*sec2)->lma)
    return -1;

  /* Sort sections with the same LMA by size.  */
  if (bfd_get_section_size (*sec1) > bfd_get_section_size (*sec2))
    return 1;
  else if (bfd_get_section_size (*sec1) < bfd_get_section_size (*sec2))
    return -1;

  return 0;
}