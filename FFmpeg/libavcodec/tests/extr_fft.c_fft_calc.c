#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  (* fft_calc ) (TYPE_1__*,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__ FFTContext ;
typedef  int /*<<< orphan*/  FFTComplex ;

/* Variables and functions */
 int /*<<< orphan*/  av_fft_calc (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void fft_calc(FFTContext *s, FFTComplex *z)
{
#if AVFFT
    av_fft_calc(s, z);
#else
    s->fft_calc(s, z);
#endif
}