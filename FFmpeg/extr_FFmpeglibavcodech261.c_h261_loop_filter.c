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
typedef  int uint8_t ;

/* Variables and functions */

__attribute__((used)) static void h261_loop_filter(uint8_t *src, int stride)
{
    int x, y, xy, yz;
    int temp[64];

    for (x = 0; x < 8; x++) {
        temp[x]         = 4 * src[x];
        temp[x + 7 * 8] = 4 * src[x + 7 * stride];
    }
    for (y = 1; y < 7; y++) {
        for (x = 0; x < 8; x++) {
            xy       = y * stride + x;
            yz       = y * 8      + x;
            temp[yz] = src[xy - stride] + 2 * src[xy] + src[xy + stride];
        }
    }

    for (y = 0; y < 8; y++) {
        src[y * stride]     = (temp[y * 8]     + 2) >> 2;
        src[y * stride + 7] = (temp[y * 8 + 7] + 2) >> 2;
        for (x = 1; x < 7; x++) {
            xy      = y * stride + x;
            yz      = y * 8      + x;
            src[xy] = (temp[yz - 1] + 2 * temp[yz] + temp[yz + 1] + 8) >> 4;
        }
    }
}