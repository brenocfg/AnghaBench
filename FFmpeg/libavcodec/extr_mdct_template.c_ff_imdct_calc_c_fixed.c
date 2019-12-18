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
struct TYPE_4__ {int mdct_bits; } ;
typedef  int /*<<< orphan*/  FFTSample ;
typedef  TYPE_1__ FFTContext ;

/* Variables and functions */
 int /*<<< orphan*/  ff_imdct_half_c (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

void ff_imdct_calc_c(FFTContext *s, FFTSample *output, const FFTSample *input)
{
    int k;
    int n = 1 << s->mdct_bits;
    int n2 = n >> 1;
    int n4 = n >> 2;

    ff_imdct_half_c(s, output+n4, input);

    for(k = 0; k < n4; k++) {
        output[k] = -output[n2-k-1];
        output[n-k-1] = output[n2+k];
    }
}