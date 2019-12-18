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
struct ieee_info {int const* pend; } ;
typedef  scalar_t__ ieee_record_enum_type ;
typedef  int bfd_vma ;
typedef  int bfd_byte ;
typedef  int /*<<< orphan*/  bfd_boolean ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  ieee_eof (struct ieee_info*) ; 
 int /*<<< orphan*/  ieee_error (struct ieee_info*,int const*,int /*<<< orphan*/ ) ; 
 scalar_t__ ieee_number_end_enum ; 
 scalar_t__ ieee_number_repeat_end_enum ; 
 scalar_t__ ieee_number_repeat_start_enum ; 

__attribute__((used)) static bfd_boolean
ieee_read_optional_number (struct ieee_info *info, const bfd_byte **pp,
			   bfd_vma *pv, bfd_boolean *ppresent)
{
  ieee_record_enum_type b;

  if (*pp >= info->pend)
    {
      if (ppresent != NULL)
	{
	  *ppresent = FALSE;
	  return TRUE;
	}
      ieee_eof (info);
      return FALSE;
    }

  b = (ieee_record_enum_type) **pp;
  ++*pp;

  if (b <= ieee_number_end_enum)
    {
      *pv = (bfd_vma) b;
      if (ppresent != NULL)
	*ppresent = TRUE;
      return TRUE;
    }

  if (b >= ieee_number_repeat_start_enum && b <= ieee_number_repeat_end_enum)
    {
      unsigned int i;

      i = (int) b - (int) ieee_number_repeat_start_enum;
      if (*pp + i - 1 >= info->pend)
	{
	  ieee_eof (info);
	  return FALSE;
	}

      *pv = 0;
      for (; i > 0; i--)
	{
	  *pv <<= 8;
	  *pv += **pp;
	  ++*pp;
	}

      if (ppresent != NULL)
	*ppresent = TRUE;

      return TRUE;
    }

  if (ppresent != NULL)
    {
      --*pp;
      *ppresent = FALSE;
      return TRUE;
    }

  ieee_error (info, *pp - 1, _("invalid number"));
  return FALSE;
}