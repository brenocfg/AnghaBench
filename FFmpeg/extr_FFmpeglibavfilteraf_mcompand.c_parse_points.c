#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int i ;
struct TYPE_5__ {int curve_dB; int nb_segments; TYPE_1__* segments; void* out_min_lin; void* in_min_lin; scalar_t__ gain_dB; } ;
struct TYPE_4__ {int x; int y; double a; int b; } ;
typedef  TYPE_2__ CompandT ;
typedef  int /*<<< orphan*/  AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 double FFMIN (double,double) ; 
 int M_LN10 ; 
 double atan2 (int,int) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 char* av_strtok (char*,char*,char**) ; 
 double cos (double) ; 
 void* exp (double) ; 
 scalar_t__ fabs (double) ; 
 double hypot (int,int) ; 
 double sin (double) ; 
 int sscanf (char*,char*,int*,int*) ; 

__attribute__((used)) static int parse_points(char *points, int nb_points, double radius,
                        CompandT *s, AVFilterContext *ctx)
{
    int new_nb_items, num;
    char *saveptr = NULL;
    char *p = points;
    int i;

#define S(x) s->segments[2 * ((x) + 1)]
    for (i = 0, new_nb_items = 0; i < nb_points; i++) {
        char *tstr = av_strtok(p, ",", &saveptr);
        p = NULL;
        if (!tstr || sscanf(tstr, "%lf/%lf", &S(i).x, &S(i).y) != 2) {
            av_log(ctx, AV_LOG_ERROR,
                    "Invalid and/or missing input/output value.\n");
            return AVERROR(EINVAL);
        }
        if (i && S(i - 1).x > S(i).x) {
            av_log(ctx, AV_LOG_ERROR,
                    "Transfer function input values must be increasing.\n");
            return AVERROR(EINVAL);
        }
        S(i).y -= S(i).x;
        av_log(ctx, AV_LOG_DEBUG, "%d: x=%f y=%f\n", i, S(i).x, S(i).y);
        new_nb_items++;
    }
    num = new_nb_items;

    /* Add 0,0 if necessary */
    if (num == 0 || S(num - 1).x)
        num++;

#undef S
#define S(x) s->segments[2 * (x)]
    /* Add a tail off segment at the start */
    S(0).x = S(1).x - 2 * s->curve_dB;
    S(0).y = S(1).y;
    num++;

    /* Join adjacent colinear segments */
    for (i = 2; i < num; i++) {
        double g1 = (S(i - 1).y - S(i - 2).y) * (S(i - 0).x - S(i - 1).x);
        double g2 = (S(i - 0).y - S(i - 1).y) * (S(i - 1).x - S(i - 2).x);
        int j;

        if (fabs(g1 - g2))
            continue;
        num--;
        for (j = --i; j < num; j++)
            S(j) = S(j + 1);
    }

    for (i = 0; i < s->nb_segments; i += 2) {
        s->segments[i].y += s->gain_dB;
        s->segments[i].x *= M_LN10 / 20;
        s->segments[i].y *= M_LN10 / 20;
    }

#define L(x) s->segments[i - (x)]
    for (i = 4; i < s->nb_segments; i += 2) {
        double x, y, cx, cy, in1, in2, out1, out2, theta, len, r;

        L(4).a = 0;
        L(4).b = (L(2).y - L(4).y) / (L(2).x - L(4).x);

        L(2).a = 0;
        L(2).b = (L(0).y - L(2).y) / (L(0).x - L(2).x);

        theta = atan2(L(2).y - L(4).y, L(2).x - L(4).x);
        len = hypot(L(2).x - L(4).x, L(2).y - L(4).y);
        r = FFMIN(radius, len);
        L(3).x = L(2).x - r * cos(theta);
        L(3).y = L(2).y - r * sin(theta);

        theta = atan2(L(0).y - L(2).y, L(0).x - L(2).x);
        len = hypot(L(0).x - L(2).x, L(0).y - L(2).y);
        r = FFMIN(radius, len / 2);
        x = L(2).x + r * cos(theta);
        y = L(2).y + r * sin(theta);

        cx = (L(3).x + L(2).x + x) / 3;
        cy = (L(3).y + L(2).y + y) / 3;

        L(2).x = x;
        L(2).y = y;

        in1  = cx - L(3).x;
        out1 = cy - L(3).y;
        in2  = L(2).x - L(3).x;
        out2 = L(2).y - L(3).y;
        L(3).a = (out2 / in2 - out1 / in1) / (in2 - in1);
        L(3).b = out1 / in1 - L(3).a * in1;
    }
    L(3).x = 0;
    L(3).y = L(2).y;

    s->in_min_lin  = exp(s->segments[1].x);
    s->out_min_lin = exp(s->segments[1].y);

    return 0;
}