#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int width; int height; } ;
struct TYPE_10__ {TYPE_1__ geometry; } ;
struct TYPE_11__ {TYPE_2__ input; int /*<<< orphan*/  output; } ;
typedef  TYPE_3__ hb_filter_private_t ;
struct TYPE_12__ {int /*<<< orphan*/ * settings; TYPE_3__* private_data; } ;
typedef  TYPE_4__ hb_filter_object_t ;
struct TYPE_13__ {int /*<<< orphan*/  human_readable_desc; int /*<<< orphan*/  output; } ;
typedef  TYPE_5__ hb_filter_info_t ;
typedef  int /*<<< orphan*/  hb_dict_t ;

/* Variables and functions */
 TYPE_5__* calloc (int,int) ; 
 int /*<<< orphan*/  hb_dict_extract_int (int*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  hb_error (char*) ; 
 int /*<<< orphan*/  hb_strdup_printf (char*,int,int,int,int,int,int,int,int,int,int) ; 

__attribute__((used)) static hb_filter_info_t * crop_scale_info( hb_filter_object_t * filter )
{
    hb_filter_private_t * pv = filter->private_data;

    if (pv == NULL)
    {
        return NULL;
    }

    hb_filter_info_t * info;
    hb_dict_t        * settings = filter->settings;
    int                width, height, top, bottom, left, right;

    info = calloc(1, sizeof(hb_filter_info_t));
    if (info == NULL)
    {
        hb_error("crop_scale_info: allocation failure");
        return NULL;
    }
    info->output = pv->output;

    hb_dict_extract_int(&top, settings, "crop-top");
    hb_dict_extract_int(&bottom, settings, "crop-bottom");
    hb_dict_extract_int(&left, settings, "crop-left");
    hb_dict_extract_int(&right, settings, "crop-right");
    hb_dict_extract_int(&width, settings, "width");
    hb_dict_extract_int(&height, settings, "height");

    int cropped_width  = pv->input.geometry.width - (left + right);
    int cropped_height = pv->input.geometry.height - (top + bottom);

    info->human_readable_desc = hb_strdup_printf(
        "source: %d * %d, crop (%d/%d/%d/%d): %d * %d, scale: %d * %d",
        pv->input.geometry.width, pv->input.geometry.height,
        top, bottom, left, right,
        cropped_width, cropped_height, width, height);

    return info;
}