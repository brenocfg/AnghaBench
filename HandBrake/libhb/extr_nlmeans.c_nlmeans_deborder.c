#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int w; int border; int /*<<< orphan*/ * mem; } ;
typedef  TYPE_1__ BorderedPlane ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void nlmeans_deborder(const BorderedPlane *src,
                             uint8_t *dst,
                             const int w,
                             const int s,
                             const int h)
{
    const int bw = src->w + 2 * src->border;
    uint8_t *image = src->mem + src->border + bw * src->border;

    int width = w;
    if (src->w < width)
    {
        width = src->w;
    }

    // Copy main image
    for (int y = 0; y < h; y++)
    {
        memcpy(dst + y * s, image + y * bw, width);
    }

}