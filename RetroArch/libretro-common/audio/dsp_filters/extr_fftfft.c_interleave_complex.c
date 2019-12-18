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

__attribute__((used)) static void interleave_complex(const unsigned *bitinverse,
      fft_complex_t *out, const fft_complex_t *in,
      unsigned samples, unsigned step)
{
   unsigned i;
   for (i = 0; i < samples; i++, in += step)
      out[bitinverse[i]] = *in;
}