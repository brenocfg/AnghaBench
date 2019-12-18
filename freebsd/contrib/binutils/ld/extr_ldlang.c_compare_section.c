#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int sort_type ;
struct TYPE_6__ {int /*<<< orphan*/  owner; } ;
typedef  TYPE_1__ asection ;

/* Variables and functions */
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  bfd_get_section_name (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int bfd_section_alignment (int /*<<< orphan*/ ,TYPE_1__*) ; 
#define  by_alignment 131 
#define  by_alignment_name 130 
#define  by_name 129 
#define  by_name_alignment 128 
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
compare_section (sort_type sort, asection *asec, asection *bsec)
{
  int ret;

  switch (sort)
    {
    default:
      abort ();

    case by_alignment_name:
      ret = (bfd_section_alignment (bsec->owner, bsec)
	     - bfd_section_alignment (asec->owner, asec));
      if (ret)
	break;
      /* Fall through.  */

    case by_name:
      ret = strcmp (bfd_get_section_name (asec->owner, asec),
		    bfd_get_section_name (bsec->owner, bsec));
      break;

    case by_name_alignment:
      ret = strcmp (bfd_get_section_name (asec->owner, asec),
		    bfd_get_section_name (bsec->owner, bsec));
      if (ret)
	break;
      /* Fall through.  */

    case by_alignment:
      ret = (bfd_section_alignment (bsec->owner, bsec)
	     - bfd_section_alignment (asec->owner, asec));
      break;
    }

  return ret;
}