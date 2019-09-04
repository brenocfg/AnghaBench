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

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void fillPlane(uint8_t *plane, int stride, int width, int height, int y,
                      uint8_t val)
{
    int i;
    uint8_t *ptr = plane + stride * y;
    for (i = 0; i < height; i++) {
        memset(ptr, val, width);
        ptr += stride;
    }
}