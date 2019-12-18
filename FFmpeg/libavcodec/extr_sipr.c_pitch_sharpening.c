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
 int SUBFR_SIZE ; 

__attribute__((used)) static void pitch_sharpening(int pitch_lag_int, float beta,
                             float *fixed_vector)
{
    int i;

    for (i = pitch_lag_int; i < SUBFR_SIZE; i++)
        fixed_vector[i] += beta * fixed_vector[i - pitch_lag_int];
}