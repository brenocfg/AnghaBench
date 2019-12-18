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
typedef  int bfd_byte ;

/* Variables and functions */

void
bfd_putb16 (bfd_vma data, void *p)
{
  bfd_byte *addr = p;
  addr[0] = (data >> 8) & 0xff;
  addr[1] = data & 0xff;
}