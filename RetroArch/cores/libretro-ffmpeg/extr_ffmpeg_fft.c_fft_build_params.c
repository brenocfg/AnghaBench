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
typedef  int /*<<< orphan*/ * vec2_t ;
typedef  int /*<<< orphan*/  fft_t ;
struct TYPE_3__ {int /*<<< orphan*/  imag; int /*<<< orphan*/  real; } ;
typedef  TYPE_1__ fft_complex_t ;
typedef  unsigned int GLuint ;

/* Variables and functions */
 float M_PI ; 
 unsigned int bitinverse (unsigned int,unsigned int) ; 
 TYPE_1__ exp_imag (float) ; 
 unsigned int vec2_packHalf2x16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void fft_build_params(fft_t *fft, GLuint *buffer,
      unsigned step, unsigned size)
{
   unsigned i, j;
   unsigned step_size = 1 << step;

   for (i = 0; i < size; i += step_size << 1)
   {
      for (j = i; j < i + step_size; j++)
      {
         vec2_t tmp;
         int s                 = j - i;
         float phase           = -1.0f * (float)s / step_size;
         unsigned a            = j;
         unsigned b            = j + step_size;
         fft_complex_t twiddle = exp_imag(M_PI * phase);

         unsigned read_a       = (step == 0) ? bitinverse(a, size) : a;
         unsigned read_b       = (step == 0) ? bitinverse(b, size) : b;

         tmp[0]                = twiddle.real;
         tmp[1]                = twiddle.imag;

         buffer[2 * a + 0]     = (read_a << 16) | read_b;
         buffer[2 * a + 1]     = vec2_packHalf2x16(tmp[0], tmp[1]);
         buffer[2 * b + 0]     = (read_a << 16) | read_b;
         buffer[2 * b + 1]     = vec2_packHalf2x16(-tmp[0], -tmp[1]);
      }
   }
}