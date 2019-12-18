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
 char bfd_get_symbol_leading_char (int /*<<< orphan*/ *) ; 

bfd_boolean
bfd_generic_is_local_label_name (bfd *abfd, const char *name)
{
  char locals_prefix = (bfd_get_symbol_leading_char (abfd) == '_') ? 'L' : '.';

  return name[0] == locals_prefix;
}