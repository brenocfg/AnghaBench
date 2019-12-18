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
typedef  int /*<<< orphan*/  bfd_vma ;
typedef  int /*<<< orphan*/  bfd_size_type ;
typedef  int /*<<< orphan*/  bfd_byte ;
typedef  int bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 int bfd_bwrite (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_putb32 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

bfd_boolean
bfd_write_bigendian_4byte_int (bfd *abfd, unsigned int i)
{
  bfd_byte buffer[4];
  bfd_putb32 ((bfd_vma) i, buffer);
  return bfd_bwrite (buffer, (bfd_size_type) 4, abfd) == 4;
}