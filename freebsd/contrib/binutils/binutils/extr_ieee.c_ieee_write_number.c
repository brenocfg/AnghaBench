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
struct ieee_handle {int dummy; } ;
typedef  scalar_t__ bfd_vma ;
typedef  int bfd_byte ;
typedef  int /*<<< orphan*/  bfd_boolean ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fprintf_vma (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ ieee_number_end_enum ; 
 scalar_t__ ieee_number_repeat_end_enum ; 
 scalar_t__ ieee_number_repeat_start_enum ; 
 int /*<<< orphan*/  ieee_write_byte (struct ieee_handle*,int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static bfd_boolean
ieee_write_number (struct ieee_handle *info, bfd_vma v)
{
  bfd_vma t;
  bfd_byte ab[20];
  bfd_byte *p;
  unsigned int c;

  if (v <= (bfd_vma) ieee_number_end_enum)
    return ieee_write_byte (info, (int) v);

  t = v;
  p = ab + sizeof ab;
  while (t != 0)
    {
      *--p = t & 0xff;
      t >>= 8;
    }
  c = (ab + 20) - p;

  if (c > (unsigned int) (ieee_number_repeat_end_enum
			  - ieee_number_repeat_start_enum))
    {
      fprintf (stderr, _("IEEE numeric overflow: 0x"));
      fprintf_vma (stderr, v);
      fprintf (stderr, "\n");
      return FALSE;
    }

  if (! ieee_write_byte (info, (int) ieee_number_repeat_start_enum + c))
    return FALSE;
  for (; c > 0; --c, ++p)
    {
      if (! ieee_write_byte (info, *p))
	return FALSE;
    }

  return TRUE;
}