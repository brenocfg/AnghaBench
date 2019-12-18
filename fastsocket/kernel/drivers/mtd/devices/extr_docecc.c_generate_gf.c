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
typedef  size_t dtype ;

/* Variables and functions */
 size_t A0 ; 
 size_t MM ; 
 int NN ; 
 scalar_t__* Pp ; 

__attribute__((used)) static void
generate_gf(dtype Alpha_to[NN + 1], dtype Index_of[NN + 1])
{
  register int i, mask;

  mask = 1;
  Alpha_to[MM] = 0;
  for (i = 0; i < MM; i++) {
    Alpha_to[i] = mask;
    Index_of[Alpha_to[i]] = i;
    /* If Pp[i] == 1 then, term @^i occurs in poly-repr of @^MM */
    if (Pp[i] != 0)
      Alpha_to[MM] ^= mask;	/* Bit-wise EXOR operation */
    mask <<= 1;	/* single left-shift */
  }
  Index_of[Alpha_to[MM]] = MM;
  /*
   * Have obtained poly-repr of @^MM. Poly-repr of @^(i+1) is given by
   * poly-repr of @^i shifted left one-bit and accounting for any @^MM
   * term that may occur when poly-repr of @^i is shifted.
   */
  mask >>= 1;
  for (i = MM + 1; i < NN; i++) {
    if (Alpha_to[i - 1] >= mask)
      Alpha_to[i] = Alpha_to[MM] ^ ((Alpha_to[i - 1] ^ mask) << 1);
    else
      Alpha_to[i] = Alpha_to[i - 1] << 1;
    Index_of[Alpha_to[i]] = i;
  }
  Index_of[0] = A0;
  Alpha_to[NN] = 0;
}