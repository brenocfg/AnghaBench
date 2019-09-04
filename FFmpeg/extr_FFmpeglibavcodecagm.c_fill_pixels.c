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
typedef  scalar_t__ uint8_t ;

/* Variables and functions */

__attribute__((used)) static int fill_pixels(uint8_t **y0, uint8_t **y1,
                       uint8_t **u, uint8_t **v,
                       int ylinesize, int ulinesize, int vlinesize,
                       uint8_t *fill,
                       int *nx, int *ny, int *np, int w, int h)
{
    uint8_t *y0dst = *y0;
    uint8_t *y1dst = *y1;
    uint8_t *udst = *u;
    uint8_t *vdst = *v;
    int x = *nx, y = *ny, pos = *np;

    if (pos == 0) {
        y0dst[2*x+0] += fill[0];
        y0dst[2*x+1] += fill[1];
        y1dst[2*x+0] += fill[2];
        y1dst[2*x+1] += fill[3];
        pos++;
    } else if (pos == 1) {
        udst[x] += fill[0];
        vdst[x] += fill[1];
        x++;
        if (x >= w) {
            x = 0;
            y++;
            if (y >= h)
                return 1;
            y0dst -= 2*ylinesize;
            y1dst -= 2*ylinesize;
            udst  -=   ulinesize;
            vdst  -=   vlinesize;
        }
        y0dst[2*x+0] += fill[2];
        y0dst[2*x+1] += fill[3];
        pos++;
    } else if (pos == 2) {
        y1dst[2*x+0] += fill[0];
        y1dst[2*x+1] += fill[1];
        udst[x]      += fill[2];
        vdst[x]      += fill[3];
        x++;
        if (x >= w) {
            x = 0;
            y++;
            if (y >= h)
                return 1;
            y0dst -= 2*ylinesize;
            y1dst -= 2*ylinesize;
            udst  -=   ulinesize;
            vdst  -=   vlinesize;
        }
        pos = 0;
    }

    *y0 = y0dst;
    *y1 = y1dst;
    *u = udst;
    *v = vdst;
    *np = pos;
    *nx = x;
    *ny = y;

    return 0;
}