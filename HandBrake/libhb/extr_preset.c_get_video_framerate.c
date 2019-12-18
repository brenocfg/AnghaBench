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
typedef  int /*<<< orphan*/  hb_value_t ;

/* Variables and functions */
 scalar_t__ HB_VALUE_TYPE_STRING ; 
 double hb_value_get_double (int /*<<< orphan*/ *) ; 
 char* hb_value_get_string (int /*<<< orphan*/ *) ; 
 scalar_t__ hb_value_type (int /*<<< orphan*/ *) ; 
 int hb_video_framerate_get_from_name (char const*) ; 
 int /*<<< orphan*/  hb_video_framerate_get_limits (int*,int*,int*) ; 
 int /*<<< orphan*/  strcasecmp (char const*,char*) ; 

__attribute__((used)) static int get_video_framerate(hb_value_t *rate_value)
{
    // Predefined by name
    if (hb_value_type(rate_value) == HB_VALUE_TYPE_STRING)
    {
        int rate = 0;
        const char *rate_name = hb_value_get_string(rate_value);
        if (!strcasecmp(rate_name, "source") ||
            !strcasecmp(rate_name, "auto") ||
            !strcasecmp(rate_name, "same as source"))
        {
            return rate;
        }
        else
        {
            rate = hb_video_framerate_get_from_name(rate_name);
            if (rate != -1)
            {
                return rate;
            }
        }
    }

    // Arbitrary
    int clock_min, clock_max, clock,
        frame_min, frame_max;
    hb_video_framerate_get_limits(&clock_min, &clock_max, &clock);
    frame_min = clock / clock_max;
    frame_max = clock / clock_min;
    double rate_d = hb_value_get_double(rate_value);
    if (rate_d >= frame_min && rate_d <= frame_max)
    {
        // Value is a framerate, return clockrate
        return (int)(clock / rate_d);
    }
    else if (rate_d >= clock_min && rate_d <= clock_max)
    {
        // Value is already a clockrate
        return (int)(rate_d);
    }

    // Value out of bounds
    return -1;
}