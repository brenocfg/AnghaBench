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
struct TYPE_6__ {double den; scalar_t__ num; } ;
typedef  TYPE_1__ hb_rational_t ;
struct TYPE_7__ {double rate; } ;
typedef  TYPE_2__ hb_rate_t ;

/* Variables and functions */
 double ABS (double) ; 
 TYPE_2__* hb_video_framerate_get_next (TYPE_2__ const*) ; 
 scalar_t__ hb_video_rate_clock ; 

int hb_video_framerate_get_close(hb_rational_t *framerate, double thresh)
{
    double            fps_in;
    const hb_rate_t * rate = NULL;
    int               result = -1;
    double            closest = thresh;

    fps_in = (double)framerate->num / framerate->den;
    while ((rate = hb_video_framerate_get_next(rate)) != NULL)
    {
        double fps = (double)hb_video_rate_clock / rate->rate;
        if (ABS(fps - fps_in) < closest)
        {
            result = rate->rate;
            closest = ABS(fps - fps_in);
        }
    }
    return result;
}