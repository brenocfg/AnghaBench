#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_7__ {int /*<<< orphan*/ ** planes; } ;
struct TYPE_6__ {int nb_planes; int* planewidth; int* planeheight; } ;
typedef  TYPE_1__ PullupContext ;
typedef  TYPE_2__ PullupBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  av_image_copy_plane (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int,int) ; 

__attribute__((used)) static void copy_field(PullupContext *s,
                       PullupBuffer *dst, PullupBuffer *src, int parity)
{
    uint8_t *dd, *ss;
    int i;

    for (i = 0; i < s->nb_planes; i++) {
        ss = src->planes[i] + parity * s->planewidth[i];
        dd = dst->planes[i] + parity * s->planewidth[i];

        av_image_copy_plane(dd, s->planewidth[i] << 1,
                            ss, s->planewidth[i] << 1,
                            s->planewidth[i], s->planeheight[i] >> 1);
    }
}