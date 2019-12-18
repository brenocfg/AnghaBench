#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct hist_node {int dummy; } ;
struct TYPE_4__ {int height; int* linesize; int width; scalar_t__* data; } ;
typedef  TYPE_1__ AVFrame ;

/* Variables and functions */
 int color_inc (struct hist_node*,scalar_t__ const) ; 

__attribute__((used)) static int update_histogram_diff(struct hist_node *hist,
                                 const AVFrame *f1, const AVFrame *f2)
{
    int x, y, ret, nb_diff_colors = 0;

    for (y = 0; y < f1->height; y++) {
        const uint32_t *p = (const uint32_t *)(f1->data[0] + y*f1->linesize[0]);
        const uint32_t *q = (const uint32_t *)(f2->data[0] + y*f2->linesize[0]);

        for (x = 0; x < f1->width; x++) {
            if (p[x] == q[x])
                continue;
            ret = color_inc(hist, p[x]);
            if (ret < 0)
                return ret;
            nb_diff_colors += ret;
        }
    }
    return nb_diff_colors;
}