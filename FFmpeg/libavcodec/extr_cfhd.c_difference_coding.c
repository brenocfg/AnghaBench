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
typedef  scalar_t__ int16_t ;

/* Variables and functions */

__attribute__((used)) static inline void difference_coding(int16_t *band, int width, int height)
{

    int i,j;
    for (i = 0; i < height; i++) {
        for (j = 1; j < width; j++) {
          band[j] += band[j-1];
        }
        band += width;
    }
}