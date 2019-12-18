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
 int /*<<< orphan*/ * ghb_array_get (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * ghb_get_title_subtitle_list (int /*<<< orphan*/ *) ; 

GhbValue *ghb_get_title_subtitle_track(GhbValue *settings, int track)
{
    GhbValue *subtitle_list  = ghb_get_title_subtitle_list(settings);
    GhbValue *subtitle_track = ghb_array_get(subtitle_list, track);
    return subtitle_track;
}