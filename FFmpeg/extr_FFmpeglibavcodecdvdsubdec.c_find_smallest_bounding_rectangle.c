#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
struct TYPE_8__ {scalar_t__ num_rects; TYPE_1__** rects; } ;
struct TYPE_7__ {scalar_t__* used_color; } ;
struct TYPE_6__ {int w; int h; int nb_colors; int** data; int* linesize; int x; int y; } ;
typedef  TYPE_2__ DVDSubContext ;
typedef  TYPE_3__ AVSubtitle ;

/* Variables and functions */
 int /*<<< orphan*/  av_freep (int**) ; 
 int* av_malloc (int) ; 
 scalar_t__ is_transp (int*,int,int,int*) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 

__attribute__((used)) static int find_smallest_bounding_rectangle(DVDSubContext *ctx, AVSubtitle *s)
{
    uint8_t transp_color[256] = { 0 };
    int y1, y2, x1, x2, y, w, h, i;
    uint8_t *bitmap;
    int transparent = 1;

    if (s->num_rects == 0 || !s->rects || s->rects[0]->w <= 0 || s->rects[0]->h <= 0)
        return 0;

    for(i = 0; i < s->rects[0]->nb_colors; i++) {
        if ((((uint32_t *)s->rects[0]->data[1])[i] >> 24) == 0) {
            transp_color[i] = 1;
        } else if (ctx->used_color[i])
            transparent = 0;
    }
    if (transparent)
        return 0;
    y1 = 0;
    while (y1 < s->rects[0]->h && is_transp(s->rects[0]->data[0] + y1 * s->rects[0]->linesize[0],
                                  1, s->rects[0]->w, transp_color))
        y1++;
    if (y1 == s->rects[0]->h) {
        av_freep(&s->rects[0]->data[0]);
        s->rects[0]->w = s->rects[0]->h = 0;
        return 0;
    }

    y2 = s->rects[0]->h - 1;
    while (y2 > 0 && is_transp(s->rects[0]->data[0] + y2 * s->rects[0]->linesize[0], 1,
                               s->rects[0]->w, transp_color))
        y2--;
    x1 = 0;
    while (x1 < (s->rects[0]->w - 1) && is_transp(s->rects[0]->data[0] + x1, s->rects[0]->linesize[0],
                                        s->rects[0]->h, transp_color))
        x1++;
    x2 = s->rects[0]->w - 1;
    while (x2 > 0 && is_transp(s->rects[0]->data[0] + x2, s->rects[0]->linesize[0], s->rects[0]->h,
                                  transp_color))
        x2--;
    w = x2 - x1 + 1;
    h = y2 - y1 + 1;
    bitmap = av_malloc(w * h);
    if (!bitmap)
        return 1;
    for(y = 0; y < h; y++) {
        memcpy(bitmap + w * y, s->rects[0]->data[0] + x1 + (y1 + y) * s->rects[0]->linesize[0], w);
    }
    av_freep(&s->rects[0]->data[0]);
    s->rects[0]->data[0] = bitmap;
    s->rects[0]->linesize[0] = w;
    s->rects[0]->w = w;
    s->rects[0]->h = h;
    s->rects[0]->x += x1;
    s->rects[0]->y += y1;

#if FF_API_AVPICTURE
FF_DISABLE_DEPRECATION_WARNINGS
    for (i = 0; i < 4; i++) {
        s->rects[0]->pict.data[i] = s->rects[0]->data[i];
        s->rects[0]->pict.linesize[i] = s->rects[0]->linesize[i];
    }
FF_ENABLE_DEPRECATION_WARNINGS
#endif

    return 1;
}