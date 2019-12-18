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
struct TYPE_3__ {unsigned int size; int /*<<< orphan*/  interleave_buffer; scalar_t__ phase_lut; int /*<<< orphan*/  bitinverse_buffer; } ;
typedef  TYPE_1__ fft_t ;
typedef  int /*<<< orphan*/  fft_complex_t ;

/* Variables and functions */
 int /*<<< orphan*/  butterflies (int /*<<< orphan*/ ,scalar_t__,int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  interleave_complex (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned int,int) ; 
 int /*<<< orphan*/  resolve_float (float*,int /*<<< orphan*/ ,unsigned int,float,unsigned int) ; 

void fft_process_inverse(fft_t *fft,
      float *out, const fft_complex_t *in, unsigned step)
{
   unsigned step_size;
   unsigned samples = fft->size;

   interleave_complex(fft->bitinverse_buffer, fft->interleave_buffer,
         in, samples, 1);

   for (step_size = 1; step_size < samples; step_size <<= 1)
   {
      butterflies(fft->interleave_buffer,
            fft->phase_lut + samples,
            1, step_size, samples);
   }

   resolve_float(out, fft->interleave_buffer, samples, 1.0f / samples, step);
}