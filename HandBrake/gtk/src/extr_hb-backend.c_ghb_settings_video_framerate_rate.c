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
typedef  int /*<<< orphan*/  GhbValue ;

/* Variables and functions */
 int /*<<< orphan*/  g_free (char*) ; 
 char* ghb_dict_get_string_xform (int /*<<< orphan*/  const*,char const*) ; 
 int ghb_lookup_video_framerate_rate (char*) ; 

int
ghb_settings_video_framerate_rate(const GhbValue *settings, const char *name)
{
    int result;
    char *rate_id = ghb_dict_get_string_xform(settings, name);
    result = ghb_lookup_video_framerate_rate(rate_id);
    g_free(rate_id);
    return result;
}