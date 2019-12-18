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
struct keypoint {int x; int y; struct keypoint* next; } ;
typedef  int /*<<< orphan*/  AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int const,int,...) ; 
 void* av_strtod (char*,char**) ; 
 struct keypoint* make_point (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int parse_points_str(AVFilterContext *ctx, struct keypoint **points, const char *s,
                            int lut_size)
{
    char *p = (char *)s; // strtod won't alter the string
    struct keypoint *last = NULL;
    const int scale = lut_size - 1;

    /* construct a linked list based on the key points string */
    while (p && *p) {
        struct keypoint *point = make_point(0, 0, NULL);
        if (!point)
            return AVERROR(ENOMEM);
        point->x = av_strtod(p, &p); if (p && *p) p++;
        point->y = av_strtod(p, &p); if (p && *p) p++;
        if (point->x < 0 || point->x > 1 || point->y < 0 || point->y > 1) {
            av_log(ctx, AV_LOG_ERROR, "Invalid key point coordinates (%f;%f), "
                   "x and y must be in the [0;1] range.\n", point->x, point->y);
            return AVERROR(EINVAL);
        }
        if (!*points)
            *points = point;
        if (last) {
            if ((int)(last->x * scale) >= (int)(point->x * scale)) {
                av_log(ctx, AV_LOG_ERROR, "Key point coordinates (%f;%f) "
                       "and (%f;%f) are too close from each other or not "
                       "strictly increasing on the x-axis\n",
                       last->x, last->y, point->x, point->y);
                return AVERROR(EINVAL);
            }
            last->next = point;
        }
        last = point;
    }

    if (*points && !(*points)->next) {
        av_log(ctx, AV_LOG_WARNING, "Only one point (at (%f;%f)) is defined, "
               "this is unlikely to behave as you expect. You probably want"
               "at least 2 points.",
               (*points)->x, (*points)->y);
    }

    return 0;
}