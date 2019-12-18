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
 int FFMAX (int,int) ; 
 int FFMIN (int,int const) ; 

__attribute__((used)) static void erosion(uint8_t *dst, const uint8_t *p1, int width,
                    int threshold, const uint8_t *coordinates[], int coord,
                    int maxc)
{
    int x, i;

    for (x = 0; x < width; x++) {
        int min = p1[x];
        int limit = FFMAX(min - threshold, 0);

        for (i = 0; i < 8; i++) {
            if (coord & (1 << i)) {
                min = FFMIN(min, *(coordinates[i] + x));
            }
            min = FFMAX(min, limit);
        }

        dst[x] = min;
    }
}