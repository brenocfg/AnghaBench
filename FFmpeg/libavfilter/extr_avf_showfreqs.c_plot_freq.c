#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_8__ {int h; int /*<<< orphan*/  frame_count_in; } ;
struct TYPE_7__ {int w; float minamp; float** avg_data; int ascale; int cmode; int nb_channels; int avg; int mode; } ;
typedef  TYPE_1__ ShowFreqsContext ;
typedef  int /*<<< orphan*/  AVFrame ;
typedef  TYPE_2__ AVFilterLink ;

/* Variables and functions */
#define  AS_CBRT 136 
#define  AS_LINEAR 135 
#define  AS_LOG 134 
#define  AS_SQRT 133 
#define  BAR 132 
#define  COMBINED 131 
#define  DOT 130 
 int FFMIN (float const,int) ; 
#define  LINE 129 
#define  SEPARATE 128 
 int /*<<< orphan*/  av_assert0 (int /*<<< orphan*/ ) ; 
 float const av_clipd (double,float const,int) ; 
 int /*<<< orphan*/  cbrt (double) ; 
 int /*<<< orphan*/  draw_dot (int /*<<< orphan*/ *,int const,int,int /*<<< orphan*/ *) ; 
 float get_bsize (TYPE_1__*,int) ; 
 int get_sx (TYPE_1__*,int) ; 
 double log (float const) ; 
 int /*<<< orphan*/  sqrt (double) ; 

__attribute__((used)) static inline void plot_freq(ShowFreqsContext *s, int ch,
                             double a, int f, uint8_t fg[4], int *prev_y,
                             AVFrame *out, AVFilterLink *outlink)
{
    const int w = s->w;
    const float min = s->minamp;
    const float avg = s->avg_data[ch][f];
    const float bsize = get_bsize(s, f);
    const int sx = get_sx(s, f);
    int end = outlink->h;
    int x, y, i;

    switch(s->ascale) {
    case AS_SQRT:
        a = 1.0 - sqrt(a);
        break;
    case AS_CBRT:
        a = 1.0 - cbrt(a);
        break;
    case AS_LOG:
        a = log(av_clipd(a, min, 1)) / log(min);
        break;
    case AS_LINEAR:
        a = 1.0 - a;
        break;
    }

    switch (s->cmode) {
    case COMBINED:
        y = a * outlink->h - 1;
        break;
    case SEPARATE:
        end = (outlink->h / s->nb_channels) * (ch + 1);
        y = (outlink->h / s->nb_channels) * ch + a * (outlink->h / s->nb_channels) - 1;
        break;
    default:
        av_assert0(0);
    }
    if (y < 0)
        return;

    switch (s->avg) {
    case 0:
        y = s->avg_data[ch][f] = !outlink->frame_count_in ? y : FFMIN(avg, y);
        break;
    case 1:
        break;
    default:
        s->avg_data[ch][f] = avg + y * (y - avg) / (FFMIN(outlink->frame_count_in + 1, s->avg) * y);
        y = s->avg_data[ch][f];
        break;
    }

    switch(s->mode) {
    case LINE:
        if (*prev_y == -1) {
            *prev_y = y;
        }
        if (y <= *prev_y) {
            for (x = sx + 1; x < sx + bsize && x < w; x++)
                draw_dot(out, x, y, fg);
            for (i = y; i <= *prev_y; i++)
                draw_dot(out, sx, i, fg);
        } else {
            for (i = *prev_y; i <= y; i++)
                draw_dot(out, sx, i, fg);
            for (x = sx + 1; x < sx + bsize && x < w; x++)
                draw_dot(out, x, i - 1, fg);
        }
        *prev_y = y;
        break;
    case BAR:
        for (x = sx; x < sx + bsize && x < w; x++)
            for (i = y; i < end; i++)
                draw_dot(out, x, i, fg);
        break;
    case DOT:
        for (x = sx; x < sx + bsize && x < w; x++)
            draw_dot(out, x, y, fg);
        break;
    }
}