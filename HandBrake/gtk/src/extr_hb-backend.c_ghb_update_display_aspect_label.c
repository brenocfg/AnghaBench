#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  settings; } ;
typedef  TYPE_1__ signal_user_data_t ;
typedef  double gint ;
typedef  int /*<<< orphan*/  gchar ;

/* Variables and functions */
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ *) ; 
 double ghb_dict_get_int (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * ghb_get_display_aspect_string (double,double) ; 
 int /*<<< orphan*/  ghb_string_value (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ghb_ui_update (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 

void
ghb_update_display_aspect_label(signal_user_data_t *ud)
{
    gint width, disp_height;
    gint par_num, par_den;
    double disp_width;
    gchar *str;

    width  = ghb_dict_get_int(ud->settings, "scale_width");
    disp_height = ghb_dict_get_int(ud->settings, "scale_height");
    par_num = ghb_dict_get_int(ud->settings, "PicturePARWidth");
    par_den = ghb_dict_get_int(ud->settings, "PicturePARHeight");
    disp_width = (double)width * par_num / par_den;
    str        = ghb_get_display_aspect_string(disp_width, disp_height);
    ghb_ui_update(ud, "display_aspect", ghb_string_value(str));
    g_free(str);
}