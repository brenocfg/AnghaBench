#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned int* bitinverse_buffer; unsigned int size; int /*<<< orphan*/ * phase_lut; int /*<<< orphan*/ * interleave_buffer; } ;
typedef  TYPE_1__ fft_t ;
typedef  int /*<<< orphan*/  fft_complex_t ;

/* Variables and functions */
 int /*<<< orphan*/  build_bitinverse (unsigned int*,unsigned int) ; 
 int /*<<< orphan*/  build_phase_lut (int /*<<< orphan*/ *,unsigned int) ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  fft_free (TYPE_1__*) ; 

fft_t *fft_new(unsigned block_size_log2)
{
   unsigned size;
   fft_t *fft = (fft_t*)calloc(1, sizeof(*fft));
   if (!fft)
      return NULL;

   size                   = 1 << block_size_log2;
   fft->interleave_buffer = (fft_complex_t*)calloc(size, sizeof(*fft->interleave_buffer));
   fft->bitinverse_buffer = (unsigned*)calloc(size, sizeof(*fft->bitinverse_buffer));
   fft->phase_lut         = (fft_complex_t*)calloc(2 * size + 1, sizeof(*fft->phase_lut));

   if (!fft->interleave_buffer || !fft->bitinverse_buffer || !fft->phase_lut)
      goto error;

   fft->size = size;

   build_bitinverse(fft->bitinverse_buffer, block_size_log2);
   build_phase_lut(fft->phase_lut, size);
   return fft;

error:
   fft_free(fft);
   return NULL;
}