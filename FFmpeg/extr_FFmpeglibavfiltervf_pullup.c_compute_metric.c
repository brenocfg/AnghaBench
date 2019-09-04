#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_9__ {int metric_plane; int* planewidth; int metric_w; int metric_length; int metric_offset; int metric_h; } ;
struct TYPE_8__ {TYPE_1__* buffer; } ;
struct TYPE_7__ {int /*<<< orphan*/ ** planes; } ;
typedef  TYPE_2__ PullupField ;
typedef  TYPE_3__ PullupContext ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void compute_metric(PullupContext *s, int *dest,
                           PullupField *fa, int pa, PullupField *fb, int pb,
                           int (*func)(const uint8_t *, const uint8_t *, ptrdiff_t))
{
    int mp = s->metric_plane;
    int xstep = 8;
    int ystep = s->planewidth[mp] << 3;
    int stride = s->planewidth[mp] << 1; /* field stride */
    int w = s->metric_w * xstep;
    uint8_t *a, *b;
    int x, y;

    if (!fa->buffer || !fb->buffer)
        return;

    /* Shortcut for duplicate fields (e.g. from RFF flag) */
    if (fa->buffer == fb->buffer && pa == pb) {
        memset(dest, 0, s->metric_length * sizeof(*dest));
        return;
    }

    a = fa->buffer->planes[mp] + pa * s->planewidth[mp] + s->metric_offset;
    b = fb->buffer->planes[mp] + pb * s->planewidth[mp] + s->metric_offset;

    for (y = 0; y < s->metric_h; y++) {
        for (x = 0; x < w; x += xstep)
            *dest++ = func(a + x, b + x, stride);
        a += ystep; b += ystep;
    }
}