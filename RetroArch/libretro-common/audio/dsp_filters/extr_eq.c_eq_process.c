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
struct eq_data {float* buffer; unsigned int block_size; unsigned int block_ptr; scalar_t__* save; int /*<<< orphan*/ * fftblock; int /*<<< orphan*/  fft; int /*<<< orphan*/ * filter; scalar_t__* block; } ;
struct dspfilter_output {float* samples; scalar_t__ frames; } ;
struct dspfilter_input {float* samples; unsigned int frames; } ;

/* Variables and functions */
 int /*<<< orphan*/  fft_complex_mul (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fft_process_forward (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*,int) ; 
 int /*<<< orphan*/  fft_process_inverse (int /*<<< orphan*/ ,float*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,float const*,int) ; 

__attribute__((used)) static void eq_process(void *data, struct dspfilter_output *output,
      const struct dspfilter_input *input)
{
   float *out;
   const float *in;
   unsigned input_frames;
   struct eq_data *eq = (struct eq_data*)data;

   output->samples    = eq->buffer;
   output->frames     = 0;

   out                = eq->buffer;
   in                 = input->samples;
   input_frames       = input->frames;

   while (input_frames)
   {
      unsigned write_avail = eq->block_size - eq->block_ptr;

      if (input_frames < write_avail)
         write_avail = input_frames;

      memcpy(eq->block + eq->block_ptr * 2, in, write_avail * 2 * sizeof(float));

      in += write_avail * 2;
      input_frames -= write_avail;
      eq->block_ptr += write_avail;

      // Convolve a new block.
      if (eq->block_ptr == eq->block_size)
      {
         unsigned i, c;

         for (c = 0; c < 2; c++)
         {
            fft_process_forward(eq->fft, eq->fftblock, eq->block + c, 2);
            for (i = 0; i < 2 * eq->block_size; i++)
               eq->fftblock[i] = fft_complex_mul(eq->fftblock[i], eq->filter[i]);
            fft_process_inverse(eq->fft, out + c, eq->fftblock, 2);
         }

         // Overlap add method, so add in saved block now.
         for (i = 0; i < 2 * eq->block_size; i++)
            out[i] += eq->save[i];

         // Save block for later.
         memcpy(eq->save, out + 2 * eq->block_size, 2 * eq->block_size * sizeof(float));

         out += eq->block_size * 2;
         output->frames += eq->block_size;
         eq->block_ptr = 0;
      }
   }
}