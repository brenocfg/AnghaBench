#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int den; int num; } ;
struct TYPE_6__ {TYPE_1__ vrate; } ;
typedef  TYPE_2__ hb_title_t ;
typedef  int gint64 ;
typedef  int /*<<< orphan*/  GhbValue ;

/* Variables and functions */
 int ghb_chapter_range_get_duration (TYPE_2__ const*,int,int) ; 
 int ghb_dict_get_int (int /*<<< orphan*/ *,char*) ; 
 int ghb_settings_combo_int (int /*<<< orphan*/ *,char*) ; 

gint64
ghb_title_range_get_duration(GhbValue * settings, const hb_title_t * title)
{
    gint64 start, end;

    if (ghb_settings_combo_int(settings, "PtoPType") == 0)
    {
        start = ghb_dict_get_int(settings, "start_point");
        end = ghb_dict_get_int(settings, "end_point");
        return ghb_chapter_range_get_duration(title, start, end) / 90000;
    }
    else if (ghb_settings_combo_int(settings, "PtoPType") == 1)
    {
        start = ghb_dict_get_int(settings, "start_point");
        end = ghb_dict_get_int(settings, "end_point");
        return end - start;
    }
    else if (ghb_settings_combo_int(settings, "PtoPType") == 2)
    {
        if (title != NULL)
        {
            gint64 frames;

            start = ghb_dict_get_int(settings, "start_point");
            end = ghb_dict_get_int(settings, "end_point");
            frames = end - start + 1;
            return frames * title->vrate.den / title->vrate.num;
        }
        else
        {
            return 0;
        }
    }
    return 0;
}