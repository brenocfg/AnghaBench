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
struct hb_filter_private_s {int dummy; } ;
typedef  int /*<<< orphan*/  hb_value_t ;
typedef  int /*<<< orphan*/  hb_list_t ;
struct TYPE_7__ {int /*<<< orphan*/  input; int /*<<< orphan*/ * avfilters; } ;
typedef  TYPE_1__ hb_filter_private_t ;
struct TYPE_8__ {int id; int aliased; int /*<<< orphan*/  settings; TYPE_1__* private_data; } ;
typedef  TYPE_2__ hb_filter_object_t ;

/* Variables and functions */
#define  HB_FILTER_AVFILTER 133 
#define  HB_FILTER_CROP_SCALE 132 
#define  HB_FILTER_DEBLOCK 131 
#define  HB_FILTER_DEINTERLACE 130 
#define  HB_FILTER_PAD 129 
#define  HB_FILTER_ROTATE 128 
 TYPE_1__* calloc (int,int) ; 
 TYPE_2__* hb_filter_init (int const) ; 
 int hb_list_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_list_insert (int /*<<< orphan*/ *,int,TYPE_2__*) ; 
 TYPE_2__* hb_list_item (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hb_value_array_concat (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_value_array_init () ; 

void hb_avfilter_combine( hb_list_t * list)
{
    hb_filter_object_t  * avfilter = NULL;
    hb_value_t          * settings = NULL;
    int                   ii;

    for (ii = 0; ii < hb_list_count(list); ii++)
    {
        hb_filter_object_t * filter = hb_list_item(list, ii);
        hb_filter_private_t * pv = filter->private_data;
        switch (filter->id)
        {
            case HB_FILTER_AVFILTER:
            case HB_FILTER_DEINTERLACE:
            case HB_FILTER_DEBLOCK:
            case HB_FILTER_CROP_SCALE:
            case HB_FILTER_PAD:
            case HB_FILTER_ROTATE:
            {
                settings = pv->avfilters;
            } break;
            default:
            {
                settings = NULL;
                avfilter = NULL;
            } break;
        }
        if (settings != NULL)
        {
            if (avfilter == NULL)
            {
                hb_filter_private_t * avpv = NULL;
                avfilter = hb_filter_init(HB_FILTER_AVFILTER);
                avfilter->aliased = 1;

                avpv = calloc(1, sizeof(struct hb_filter_private_s));
                avfilter->private_data = avpv;
                avpv->input = pv->input;

                avfilter->settings = hb_value_array_init();
                hb_list_insert(list, ii, avfilter);
                ii++;
            }

            hb_value_array_concat(avfilter->settings, settings);
        }
    }
}