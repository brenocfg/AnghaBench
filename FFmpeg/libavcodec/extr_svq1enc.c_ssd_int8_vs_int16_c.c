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
typedef  int int8_t ;
typedef  int int16_t ;

/* Variables and functions */

__attribute__((used)) static int ssd_int8_vs_int16_c(const int8_t *pix1, const int16_t *pix2,
                               intptr_t size)
{
    int score = 0, i;

    for (i = 0; i < size; i++)
        score += (pix1[i] - pix2[i]) * (pix1[i] - pix2[i]);
    return score;
}