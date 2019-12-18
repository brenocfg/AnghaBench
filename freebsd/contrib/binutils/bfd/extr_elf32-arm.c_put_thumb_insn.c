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
struct elf32_arm_link_hash_table {scalar_t__ byteswap_code; } ;
typedef  int /*<<< orphan*/  bfd_vma ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 scalar_t__ bfd_little_endian (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_putb16 (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  bfd_putl16 (int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static void
put_thumb_insn (struct elf32_arm_link_hash_table *htab,
	       bfd * output_bfd, bfd_vma val, void * ptr)
{
    if (htab->byteswap_code != bfd_little_endian (output_bfd))
      bfd_putl16 (val, ptr);
    else
      bfd_putb16 (val, ptr);
}