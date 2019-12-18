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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  void* uint16_t ;

/* Variables and functions */
 scalar_t__ AV_RN16A (int /*<<< orphan*/  const*) ; 
 scalar_t__ FFMAX (int,scalar_t__) ; 
 void* FFMIN (scalar_t__,int) ; 

__attribute__((used)) static void inflate16(uint8_t *dstp, const uint8_t *p1, int width,
                      int threshold, const uint8_t *coordinates[], int coord,
                      int maxc)
{
    uint16_t *dst = (uint16_t *)dstp;
    int x, i;

    for (x = 0; x < width; x++) {
        int sum = 0;
        int limit = FFMIN(AV_RN16A(&p1[2 * x]) + threshold, maxc);

        for (i = 0; i < 8; sum += AV_RN16A(coordinates[i++] + x * 2));

        dst[x] = FFMIN(FFMAX(sum / 8, AV_RN16A(&p1[x * 2])), limit);
    }
}