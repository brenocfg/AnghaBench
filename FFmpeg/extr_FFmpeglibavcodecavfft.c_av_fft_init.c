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
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * av_mallocz (int) ; 
 scalar_t__ ff_fft_init (int /*<<< orphan*/ *,int,int) ; 

FFTContext *av_fft_init(int nbits, int inverse)
{
    FFTContext *s = av_mallocz(sizeof(*s));

    if (s && ff_fft_init(s, nbits, inverse))
        av_freep(&s);

    return s;
}