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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int COLOR (int) ; 
 int GRAY (int) ; 
 int /*<<< orphan*/  ff_cga_palette ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void set_palette(uint32_t *pal)
{
    int r, g, b;
    memcpy(pal, ff_cga_palette, 16 * 4);
    pal += 16;
#define COLOR(x) ((x) * 40 + 55)
    for (r = 0; r < 6; r++)
        for (g = 0; g < 6; g++)
            for (b = 0; b < 6; b++)
                *pal++ = 0xFF000000 | (COLOR(r) << 16) | (COLOR(g) << 8) | COLOR(b);
#define GRAY(x) ((x) * 10 + 8)
    for (g = 0; g < 24; g++)
        *pal++ = 0xFF000000 | (GRAY(g) << 16) | (GRAY(g) << 8) | GRAY(g);
}