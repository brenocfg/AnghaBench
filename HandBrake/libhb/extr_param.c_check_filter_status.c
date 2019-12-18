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
#define  HB_FILTER_ROTATE 128 
 int hb_dict_get_int (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  hb_dict_set (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_value_bool (int) ; 

__attribute__((used)) static void check_filter_status(int filter_id, hb_value_t *settings)
{
    int disable = 0;

    if (settings == NULL)
    {
        return;
    }
    switch (filter_id)
    {
        case HB_FILTER_ROTATE:
        {
            int angle = hb_dict_get_int(settings, "angle");
            int hflip = hb_dict_get_int(settings, "hflip");
            disable = angle == 0 && hflip == 0;
        } break;
        default:
        {
        } break;
    }
    if (disable)
    {
        hb_dict_set(settings, "disable", hb_value_bool(disable));
    }
}