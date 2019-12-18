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
typedef  int /*<<< orphan*/  fft_complex_t ;

/* Variables and functions */
 int /*<<< orphan*/  butterfly (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const) ; 

__attribute__((used)) static void butterflies(fft_complex_t *butterfly_buf,
      const fft_complex_t *phase_lut,
      int phase_dir, unsigned step_size, unsigned samples)
{
   unsigned i, j;
   for (i = 0; i < samples; i += step_size << 1)
   {
      int phase_step = (int)samples * phase_dir / (int)step_size;
      for (j = i; j < i + step_size; j++)
         butterfly(&butterfly_buf[j], &butterfly_buf[j + step_size],
               phase_lut[phase_step * (int)(j - i)]);
   }
}