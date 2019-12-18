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
typedef  int /*<<< orphan*/  FFTContext ;

/* Variables and functions */
 int /*<<< orphan*/ * av_fft_init (int,int) ; 
 int /*<<< orphan*/  ff_fft_init (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static inline void fft_init(FFTContext **s, int nbits, int inverse)
{
#if AVFFT
    *s = av_fft_init(nbits, inverse);
#else
    ff_fft_init(*s, nbits, inverse);
#endif
}