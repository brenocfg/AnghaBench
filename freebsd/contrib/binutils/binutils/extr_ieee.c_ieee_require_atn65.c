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
struct ieee_info {int dummy; } ;
typedef  scalar_t__ ieee_record_enum_type ;
typedef  scalar_t__ bfd_vma ;
typedef  unsigned int bfd_byte ;
typedef  int /*<<< orphan*/  bfd_boolean ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ ieee_at_record_enum ; 
 scalar_t__ ieee_atn_record_enum ; 
 int /*<<< orphan*/  ieee_error (struct ieee_info*,unsigned int const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee_read_id (struct ieee_info*,unsigned int const**,char const**,unsigned long*) ; 
 int /*<<< orphan*/  ieee_read_number (struct ieee_info*,unsigned int const**,scalar_t__*) ; 

__attribute__((used)) static bfd_boolean
ieee_require_atn65 (struct ieee_info *info, const bfd_byte **pp,
		    const char **pname, unsigned long *pnamlen)
{
  const bfd_byte *start;
  ieee_record_enum_type c;
  bfd_vma name_indx, type_indx, atn_code;

  start = *pp;

  c = (ieee_record_enum_type) **pp;
  if (c != ieee_at_record_enum)
    {
      ieee_error (info, start, _("missing required ATN65"));
      return FALSE;
    }
  ++*pp;

  c = (ieee_record_enum_type) (((unsigned int) c << 8) | **pp);
  if (c != ieee_atn_record_enum)
    {
      ieee_error (info, start, _("missing required ATN65"));
      return FALSE;
    }
  ++*pp;

  if (! ieee_read_number (info, pp, &name_indx)
      || ! ieee_read_number (info, pp, &type_indx)
      || ! ieee_read_number (info, pp, &atn_code))
    return FALSE;

  /* Just ignore name_indx.  */

  if (type_indx != 0 || atn_code != 65)
    {
      ieee_error (info, start, _("bad ATN65 record"));
      return FALSE;
    }

  return ieee_read_id (info, pp, pname, pnamlen);
}