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
struct TYPE_3__ {double* band_centre; int sample_rate; } ;
typedef  TYPE_1__ AudioFFTDeNoiseContext ;

/* Variables and functions */
 int FFMIN (int,int) ; 
 int lrint (double) ; 

__attribute__((used)) static int get_band_edge(AudioFFTDeNoiseContext *s, int band)
{
    int i;

    if (band == 15) {
        i = lrint(s->band_centre[14] * 1.224745);
    } else {
        i = lrint(s->band_centre[band] / 1.224745);
    }

    return FFMIN(i, s->sample_rate / 2);
}