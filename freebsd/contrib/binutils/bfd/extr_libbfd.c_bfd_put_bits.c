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
typedef  int bfd_uint64_t ;
typedef  int bfd_byte ;
typedef  scalar_t__ bfd_boolean ;

/* Variables and functions */
 int /*<<< orphan*/  abort () ; 

void
bfd_put_bits (bfd_uint64_t data, void *p, int bits, bfd_boolean big_p)
{
  bfd_byte *addr = p;
  int i;
  int bytes;

  if (bits % 8 != 0)
    abort ();

  bytes = bits / 8;
  for (i = 0; i < bytes; i++)
    {
      int index = big_p ? bytes - i - 1 : i;

      addr[index] = data & 0xff;
      data >>= 8;
    }
}