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
typedef  int ptrdiff_t ;

/* Variables and functions */
 int MAX_NEG_CROP ; 
 int* ff_crop_tab ; 

__attribute__((used)) static void intra_pred_plane(uint8_t *d, uint8_t *top, uint8_t *left, ptrdiff_t stride)
{
    int x, y, ia;
    int ih = 0;
    int iv = 0;
    const uint8_t *cm = ff_crop_tab + MAX_NEG_CROP;

    for (x = 0; x < 4; x++) {
        ih += (x + 1) *  (top[5 + x] -  top[3 - x]);
        iv += (x + 1) * (left[5 + x] - left[3 - x]);
    }
    ia = (top[8] + left[8]) << 4;
    ih = (17 * ih + 16) >> 5;
    iv = (17 * iv + 16) >> 5;
    for (y = 0; y < 8; y++)
        for (x = 0; x < 8; x++)
            d[y * stride + x] = cm[(ia + (x - 3) * ih + (y - 3) * iv + 16) >> 5];
}