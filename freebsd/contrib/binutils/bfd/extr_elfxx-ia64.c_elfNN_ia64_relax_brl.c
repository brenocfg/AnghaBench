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
typedef  int bfd_vma ;
typedef  int /*<<< orphan*/  bfd_byte ;

/* Variables and functions */
 int bfd_getl64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_putl64 (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
elfNN_ia64_relax_brl (bfd_byte *contents, bfd_vma off)
{
  int template;
  bfd_byte *hit_addr;
  bfd_vma t0, t1, i0, i1, i2;

  hit_addr = (bfd_byte *) (contents + off);
  hit_addr -= (long) hit_addr & 0x3;
  t0 = bfd_getl64 (hit_addr);
  t1 = bfd_getl64 (hit_addr + 8);

  /* Keep the instruction in slot 0. */
  i0 = (t0 >> 5) & 0x1ffffffffffLL;
  /* Use nop.b for slot 1. */
  i1 = 0x4000000000LL;
  /* For slot 2, turn brl into br by masking out bit 40.  */
  i2 = (t1 >> 23) & 0x0ffffffffffLL;

  /* Turn a MLX bundle into a MBB bundle with the same stop-bit
     variety.  */
  if (t0 & 0x1)
    template = 0x13;
  else
    template = 0x12;
  t0 = (i1 << 46) | (i0 << 5) | template;
  t1 = (i2 << 23) | (i1 >> 18);

  bfd_putl64 (t0, hit_addr);
  bfd_putl64 (t1, hit_addr + 8);
}