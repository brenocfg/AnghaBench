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
struct TYPE_3__ {int width; int height; int /*<<< orphan*/  abbr; } ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EINVAL ; 
 int FF_ARRAY_ELEMS (TYPE_1__*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 
 int strtol (char const*,void*,int) ; 
 TYPE_1__* video_size_abbrs ; 

int av_parse_video_size(int *width_ptr, int *height_ptr, const char *str)
{
    int i;
    int n = FF_ARRAY_ELEMS(video_size_abbrs);
    const char *p;
    int width = 0, height = 0;

    for (i = 0; i < n; i++) {
        if (!strcmp(video_size_abbrs[i].abbr, str)) {
            width  = video_size_abbrs[i].width;
            height = video_size_abbrs[i].height;
            break;
        }
    }
    if (i == n) {
        width = strtol(str, (void*)&p, 10);
        if (*p)
            p++;
        height = strtol(p, (void*)&p, 10);

        /* trailing extraneous data detected, like in 123x345foobar */
        if (*p)
            return AVERROR(EINVAL);
    }
    if (width <= 0 || height <= 0)
        return AVERROR(EINVAL);
    *width_ptr  = width;
    *height_ptr = height;
    return 0;
}