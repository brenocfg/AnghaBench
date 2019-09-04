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
 int FFABS (int) ; 

__attribute__((used)) static void setup_5x5(int radius, const uint8_t *c[], const uint8_t *src, int stride,
                      int x, int w, int y, int h, int bpc)
{
    int i;

    for (i = 0; i < 25; i++) {
        int xoff = FFABS(x + ((i % 5) - 2));
        int yoff = FFABS(y + (i / 5) - 2);

        xoff = xoff >= w ? 2 * w - 1 - xoff : xoff;
        yoff = yoff >= h ? 2 * h - 1 - yoff : yoff;

        c[i] = src + xoff * bpc + yoff * stride;
    }
}