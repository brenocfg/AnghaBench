#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int offsetT ;
struct TYPE_3__ {int fr_offset; scalar_t__ fr_symbol; } ;
typedef  TYPE_1__ fragS ;

/* Variables and functions */

__attribute__((used)) static int
relax_immediate (fragS *fragp, int size, int shift)
{
  offsetT offset;
  offsetT mask;
  offsetT low;

  /* ??? Should be able to do better than this.  */
  if (fragp->fr_symbol)
    return 4;

  low = (1 << shift) - 1;
  mask = (1 << (shift + size)) - (1 << shift);
  offset = fragp->fr_offset;
  /* Force misaligned offsets to 32-bit variant.  */
  if (offset & low)
    return 4;
  if (offset & ~mask)
    return 4;
  return 2;
}