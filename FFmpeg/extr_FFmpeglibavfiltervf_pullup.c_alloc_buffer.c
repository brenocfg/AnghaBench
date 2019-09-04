#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {void** planes; } ;
struct TYPE_5__ {int nb_planes; int* planeheight; int* planewidth; } ;
typedef  TYPE_1__ PullupContext ;
typedef  TYPE_2__ PullupBuffer ;

/* Variables and functions */
 void* av_malloc (int) ; 

__attribute__((used)) static int alloc_buffer(PullupContext *s, PullupBuffer *b)
{
    int i;

    if (b->planes[0])
        return 0;
    for (i = 0; i < s->nb_planes; i++) {
        b->planes[i] = av_malloc(s->planeheight[i] * s->planewidth[i]);
    }
    if (s->nb_planes == 1)
        b->planes[1] = av_malloc(4*256);

    return 0;
}