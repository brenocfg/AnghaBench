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
typedef  int /*<<< orphan*/  selective ;
typedef  int /*<<< orphan*/  hb_list_t ;
struct TYPE_7__ {int width; int height; } ;
typedef  TYPE_1__ hb_geometry_t ;
struct TYPE_8__ {int /*<<< orphan*/ * settings; } ;
typedef  TYPE_2__ hb_filter_object_t ;
typedef  int /*<<< orphan*/  hb_dict_t ;

/* Variables and functions */
 int HB_FILTER_COMB_DETECT ; 
 int HB_FILTER_CROP_SCALE ; 
 int HB_FILTER_DECOMB ; 
 int HB_FILTER_DEINTERLACE ; 
 int HB_FILTER_DETELECINE ; 
 int HB_FILTER_VFR ; 
 int MODE_DECOMB_SELECTIVE ; 
 int hb_dict_get_int (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  hb_dict_set (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_filter_close (TYPE_2__**) ; 
 TYPE_2__* hb_filter_find (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hb_list_rem (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  hb_log (char*) ; 
 int /*<<< orphan*/  hb_value_int (int) ; 

__attribute__((used)) static void sanitize_filter_list(hb_list_t *list, hb_geometry_t src_geo)
{
    // Add selective deinterlacing mode if comb detection is enabled
    if (hb_filter_find(list, HB_FILTER_COMB_DETECT) != NULL)
    {
        int selective[] = {HB_FILTER_DECOMB, HB_FILTER_DEINTERLACE};
        int ii, count = sizeof(selective) / sizeof(int);

        for (ii = 0; ii < count; ii++)
        {
            hb_filter_object_t * filter = hb_filter_find(list, selective[ii]);
            if (filter != NULL)
            {
                int mode = hb_dict_get_int(filter->settings, "mode");
                mode |= MODE_DECOMB_SELECTIVE;
                hb_dict_set(filter->settings, "mode", hb_value_int(mode));
                break;
            }
        }
    }

    int is_detel = 0;
    hb_filter_object_t * filter = hb_filter_find(list, HB_FILTER_DETELECINE);
    if (filter != NULL)
    {
        is_detel = 1;
    }

    filter = hb_filter_find(list, HB_FILTER_VFR);
    if (filter != NULL)
    {
        int mode = hb_dict_get_int(filter->settings, "mode");
        // "Same as source" FPS and no HB_FILTER_DETELECINE
        if ( (mode == 0) && (is_detel == 0) )
        {
            hb_list_rem(list, filter);
            hb_filter_close(&filter);
            hb_log("Skipping vfr filter");
        }
    }

    filter = hb_filter_find(list, HB_FILTER_CROP_SCALE);
    if (filter != NULL)
    {
        hb_dict_t* settings = filter->settings;
        if (settings != NULL)
        {
            int width, height, top, bottom, left, right;
            width = hb_dict_get_int(settings, "width");
            height = hb_dict_get_int(settings, "height");
            top = hb_dict_get_int(settings, "crop-top");
            bottom = hb_dict_get_int(settings, "crop-bottom");
            left = hb_dict_get_int(settings, "crop-left");
            right = hb_dict_get_int(settings, "crop-right");

            if ( (src_geo.width == width) && (src_geo.height == height) &&
                (top == 0) && (bottom == 0 ) && (left == 0) && (right == 0) )
            {
                hb_list_rem(list, filter);
                hb_filter_close(&filter);
                hb_log("Skipping crop/scale filter");
            }
        }
    }
}