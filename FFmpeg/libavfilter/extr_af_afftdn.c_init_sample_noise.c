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
struct TYPE_3__ {double* noise_band_norm; double* noise_band_avr; double* noise_band_avi; double* noise_band_var; } ;
typedef  TYPE_1__ DeNoiseChannel ;

/* Variables and functions */

__attribute__((used)) static void init_sample_noise(DeNoiseChannel *dnch)
{
    for (int i = 0; i < 15; i++) {
        dnch->noise_band_norm[i] = 0.0;
        dnch->noise_band_avr[i] = 0.0;
        dnch->noise_band_avi[i] = 0.0;
        dnch->noise_band_var[i] = 0.0;
    }
}