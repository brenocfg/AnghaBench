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
struct TYPE_3__ {double* band_centre; } ;
typedef  TYPE_1__ AudioFFTDeNoiseContext ;

/* Variables and functions */
 int lrint (double) ; 

__attribute__((used)) static int get_band_centre(AudioFFTDeNoiseContext *s, int band)
{
    if (band == -1)
        return lrint(s->band_centre[0] / 1.5);

    return s->band_centre[band];
}