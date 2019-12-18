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
typedef  int bfd_byte ;
typedef  int /*<<< orphan*/  bfd_boolean ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  ieee_eof (struct ieee_info*) ; 
 int /*<<< orphan*/  ieee_error (struct ieee_info*,int const*,int /*<<< orphan*/ ) ; 
 scalar_t__ ieee_extension_length_1_enum ; 
 scalar_t__ ieee_extension_length_2_enum ; 

__attribute__((used)) static bfd_boolean
ieee_read_optional_id (struct ieee_info *info, const bfd_byte **pp,
		       const char **pname, unsigned long *pnamlen,
		       bfd_boolean *ppresent)
{
  bfd_byte b;
  unsigned long len;

  if (*pp >= info->pend)
    {
      ieee_eof (info);
      return FALSE;
    }

  b = **pp;
  ++*pp;

  if (b <= 0x7f)
    len = b;
  else if ((ieee_record_enum_type) b == ieee_extension_length_1_enum)
    {
      len = **pp;
      ++*pp;
    }
  else if ((ieee_record_enum_type) b == ieee_extension_length_2_enum)
    {
      len = (**pp << 8) + (*pp)[1];
      *pp += 2;
    }
  else
    {
      if (ppresent != NULL)
	{
	  --*pp;
	  *ppresent = FALSE;
	  return TRUE;
	}
      ieee_error (info, *pp - 1, _("invalid string length"));
      return FALSE;
    }

  if ((unsigned long) (info->pend - *pp) < len)
    {
      ieee_eof (info);
      return FALSE;
    }

  *pname = (const char *) *pp;
  *pnamlen = len;
  *pp += len;

  if (ppresent != NULL)
    *ppresent = TRUE;

  return TRUE;
}