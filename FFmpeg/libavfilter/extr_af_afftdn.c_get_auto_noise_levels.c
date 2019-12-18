#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int noise_band_count; int floor; } ;
struct TYPE_5__ {int* noise_band_auto_var; } ;
typedef  TYPE_1__ DeNoiseChannel ;
typedef  TYPE_2__ AudioFFTDeNoiseContext ;

/* Variables and functions */
 double C ; 
 double log (int) ; 

__attribute__((used)) static void get_auto_noise_levels(AudioFFTDeNoiseContext *s,
                                  DeNoiseChannel *dnch,
                                  double *levels)
{
    if (s->noise_band_count > 0) {
        for (int i = 0; i < s->noise_band_count; i++) {
            levels[i] = (1.0 / C) * log(dnch->noise_band_auto_var[i] / s->floor) - 100.0;
        }
        if (s->noise_band_count < 15) {
            for (int i = s->noise_band_count; i < 15; i++)
                levels[i] = levels[i - 1];
        }
    } else {
        for (int i = 0; i < 15; i++) {
            levels[i] = -100.0;
        }
    }
}