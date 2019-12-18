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

/* Variables and functions */

void ff_vorbis_inverse_coupling(float *mag, float *ang, intptr_t blocksize)
{
    int i;
    for (i = 0;  i < blocksize;  i++) {
        if (mag[i] > 0.0) {
            if (ang[i] > 0.0) {
                ang[i] = mag[i] - ang[i];
            } else {
                float temp = ang[i];
                ang[i]     = mag[i];
                mag[i]    += temp;
            }
        } else {
            if (ang[i] > 0.0) {
                ang[i] += mag[i];
            } else {
                float temp = ang[i];
                ang[i]     = mag[i];
                mag[i]    -= temp;
            }
        }
    }
}