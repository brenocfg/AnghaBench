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

/* Variables and functions */
 int /*<<< orphan*/  abort () ; 

__attribute__((used)) static void
neon_invert_size (unsigned *xlo, unsigned *xhi, int size)
{
  unsigned immlo = xlo ? *xlo : 0;
  unsigned immhi = xhi ? *xhi : 0;

  switch (size)
    {
    case 8:
      immlo = (~immlo) & 0xff;
      break;

    case 16:
      immlo = (~immlo) & 0xffff;
      break;

    case 64:
      immhi = (~immhi) & 0xffffffff;
      /* fall through.  */

    case 32:
      immlo = (~immlo) & 0xffffffff;
      break;

    default:
      abort ();
    }

  if (xlo)
    *xlo = immlo;

  if (xhi)
    *xhi = immhi;
}