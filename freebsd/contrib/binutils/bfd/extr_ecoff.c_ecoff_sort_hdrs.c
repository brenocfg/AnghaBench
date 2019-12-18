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
struct TYPE_2__ {int flags; scalar_t__ vma; } ;
typedef  TYPE_1__ asection ;

/* Variables and functions */
 int SEC_ALLOC ; 

__attribute__((used)) static int
ecoff_sort_hdrs (const void * arg1, const void * arg2)
{
  const asection *hdr1 = *(const asection **) arg1;
  const asection *hdr2 = *(const asection **) arg2;

  if ((hdr1->flags & SEC_ALLOC) != 0)
    {
      if ((hdr2->flags & SEC_ALLOC) == 0)
	return -1;
    }
  else
    {
      if ((hdr2->flags & SEC_ALLOC) != 0)
	return 1;
    }
  if (hdr1->vma < hdr2->vma)
    return -1;
  else if (hdr1->vma > hdr2->vma)
    return 1;
  else
    return 0;
}