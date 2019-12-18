#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int /*<<< orphan*/ * outputs; TYPE_2__* priv; } ;
struct TYPE_17__ {TYPE_5__* dst; } ;
struct TYPE_16__ {int width; int height; } ;
struct TYPE_15__ {unsigned int* d; int* s; int x; int y; int* S; int nb_planes; size_t front; size_t back; TYPE_1__* points; int /*<<< orphan*/  (* set_pixel ) (TYPE_3__*,int,int,unsigned int const,unsigned int const,unsigned int const,unsigned int const) ;scalar_t__ (* is_same ) (TYPE_3__*,int,int,int,int,int,int) ;int /*<<< orphan*/  (* pick_pixel ) (TYPE_3__*,int,int,int*,int*,int*,int*) ;} ;
struct TYPE_14__ {int x; int y; } ;
typedef  TYPE_2__ FloodfillContext ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVFilterLink ;
typedef  TYPE_5__ AVFilterContext ;

/* Variables and functions */
 int av_frame_make_writable (TYPE_3__*) ; 
 int ff_filter_frame (int /*<<< orphan*/ ,TYPE_3__*) ; 
 scalar_t__ is_inside (int,int,int const,int const) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int,int,int*,int*,int*,int*) ; 
 scalar_t__ stub2 (TYPE_3__*,int,int,int,int,int,int) ; 
 scalar_t__ stub3 (TYPE_3__*,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  stub4 (TYPE_3__*,int,int,unsigned int const,unsigned int const,unsigned int const,unsigned int const) ; 

__attribute__((used)) static int filter_frame(AVFilterLink *link, AVFrame *frame)
{
    AVFilterContext *ctx = link->dst;
    FloodfillContext *s = ctx->priv;
    const unsigned d0 = s->d[0];
    const unsigned d1 = s->d[1];
    const unsigned d2 = s->d[2];
    const unsigned d3 = s->d[3];
    int s0 = s->s[0];
    int s1 = s->s[1];
    int s2 = s->s[2];
    int s3 = s->s[3];
    const int w = frame->width;
    const int h = frame->height;
    int i, ret;

    if (is_inside(s->x, s->y, w, h)) {
        s->pick_pixel(frame, s->x, s->y, &s0, &s1, &s2, &s3);

        s->S[0] = s0;
        s->S[1] = s1;
        s->S[2] = s2;
        s->S[3] = s3;
        for (i = 0; i < s->nb_planes; i++) {
            if (s->S[i] != s->d[i])
                break;
        }

        if (i == s->nb_planes)
            goto end;

        if (s->is_same(frame, s->x, s->y, s0, s1, s2, s3)) {
            s->points[s->front].x = s->x;
            s->points[s->front].y = s->y;
            s->front++;
        }

        if (ret = av_frame_make_writable(frame))
            return ret;

        while (s->front > s->back) {
            int x, y;

            s->front--;
            x = s->points[s->front].x;
            y = s->points[s->front].y;

            if (s->is_same(frame, x, y, s0, s1, s2, s3)) {
                s->set_pixel(frame, x, y, d0, d1, d2, d3);

                if (is_inside(x + 1, y, w, h)) {
                    s->points[s->front]  .x = x + 1;
                    s->points[s->front++].y = y;
                }

                if (is_inside(x - 1, y, w, h)) {
                    s->points[s->front]  .x = x - 1;
                    s->points[s->front++].y = y;
                }

                if (is_inside(x, y + 1, w, h)) {
                    s->points[s->front]  .x = x;
                    s->points[s->front++].y = y + 1;
                }

                if (is_inside(x, y - 1, w, h)) {
                    s->points[s->front]  .x = x;
                    s->points[s->front++].y = y - 1;
                }
            }
        }
    }

end:
    return ff_filter_frame(ctx->outputs[0], frame);
}