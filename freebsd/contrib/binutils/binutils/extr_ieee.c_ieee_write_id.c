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
typedef  int /*<<< orphan*/  bfd_boolean ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,unsigned int) ; 
 scalar_t__ ieee_extension_length_1_enum ; 
 scalar_t__ ieee_extension_length_2_enum ; 
 int /*<<< orphan*/  ieee_write_2bytes (struct ieee_handle*,unsigned int) ; 
 int /*<<< orphan*/  ieee_write_byte (struct ieee_handle*,char const) ; 
 int /*<<< orphan*/  stderr ; 
 unsigned int strlen (char const*) ; 

__attribute__((used)) static bfd_boolean
ieee_write_id (struct ieee_handle *info, const char *s)
{
  unsigned int len;

  len = strlen (s);
  if (len <= 0x7f)
    {
      if (! ieee_write_byte (info, len))
	return FALSE;
    }
  else if (len <= 0xff)
    {
      if (! ieee_write_byte (info, (int) ieee_extension_length_1_enum)
	  || ! ieee_write_byte (info, len))
	return FALSE;
    }
  else if (len <= 0xffff)
    {
      if (! ieee_write_byte (info, (int) ieee_extension_length_2_enum)
	  || ! ieee_write_2bytes (info, len))
	return FALSE;
    }
  else
    {
      fprintf (stderr, _("IEEE string length overflow: %u\n"), len);
      return FALSE;
    }

  for (; *s != '\0'; s++)
    if (! ieee_write_byte (info, *s))
      return FALSE;

  return TRUE;
}