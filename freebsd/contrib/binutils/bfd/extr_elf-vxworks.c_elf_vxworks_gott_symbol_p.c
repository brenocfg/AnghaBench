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
typedef  int bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 int FALSE ; 
 char bfd_get_symbol_leading_char (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static bfd_boolean
elf_vxworks_gott_symbol_p (bfd *abfd, const char *name)
{
  char leading;

  leading = bfd_get_symbol_leading_char (abfd);
  if (leading)
    {
      if (*name != leading)
	return FALSE;
      name++;
    }
  return (strcmp (name, "__GOTT_BASE__") == 0
	  || strcmp (name, "__GOTT_INDEX__") == 0);
}