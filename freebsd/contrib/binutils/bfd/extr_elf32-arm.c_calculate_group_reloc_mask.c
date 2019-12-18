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

/* Variables and functions */

__attribute__((used)) static bfd_vma
calculate_group_reloc_mask (bfd_vma value, int n, bfd_vma *final_residual)
{
  int current_n;
  bfd_vma g_n;
  bfd_vma encoded_g_n = 0;
  bfd_vma residual = value; /* Also known as Y_n.  */

  for (current_n = 0; current_n <= n; current_n++)
    {
      int shift;

      /* Calculate which part of the value to mask.  */
      if (residual == 0)
        shift = 0;
      else
        {
          int msb;

          /* Determine the most significant bit in the residual and
             align the resulting value to a 2-bit boundary.  */
          for (msb = 30; msb >= 0; msb -= 2)
            if (residual & (3 << msb))
              break;

          /* The desired shift is now (msb - 6), or zero, whichever
             is the greater.  */
          shift = msb - 6;
          if (shift < 0)
            shift = 0;
        }

      /* Calculate g_n in 32-bit as well as encoded constant+rotation form.  */
      g_n = residual & (0xff << shift);
      encoded_g_n = (g_n >> shift)
                    | ((g_n <= 0xff ? 0 : (32 - shift) / 2) << 8);

      /* Calculate the residual for the next time around.  */
      residual &= ~g_n;
    }

  *final_residual = residual;

  return encoded_g_n;
}