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
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 int /*<<< orphan*/  _bfd_elf_write_object_contents (int /*<<< orphan*/ *) ; 

bfd_boolean
_bfd_elf_write_corefile_contents (bfd *abfd)
{
  /* Hopefully this can be done just like an object file.  */
  return _bfd_elf_write_object_contents (abfd);
}