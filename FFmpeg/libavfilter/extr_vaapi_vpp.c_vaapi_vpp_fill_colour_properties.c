#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VAProcColorStandardType ;
struct TYPE_6__ {int /*<<< orphan*/  va_color_range; int /*<<< orphan*/  va_chroma_sample_location; int /*<<< orphan*/  va_color_standard; int /*<<< orphan*/  chroma_sample_location; int /*<<< orphan*/  color_trc; int /*<<< orphan*/  color_primaries; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  color_range; } ;
typedef  TYPE_1__ VAAPIColourProperties ;
typedef  int /*<<< orphan*/  AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  av_chroma_location_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_color_primaries_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_color_range_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_color_space_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_color_transfer_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vaapi_vpp_fill_chroma_sample_location (TYPE_1__*) ; 
 int /*<<< orphan*/  vaapi_vpp_fill_colour_range (TYPE_1__*) ; 
 int /*<<< orphan*/  vaapi_vpp_fill_colour_standard (TYPE_1__*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void vaapi_vpp_fill_colour_properties(AVFilterContext *avctx,
                                             VAAPIColourProperties *props,
                                             VAProcColorStandardType *vacs,
                                             int nb_vacs)
{
    vaapi_vpp_fill_colour_standard(props, vacs, nb_vacs);
    vaapi_vpp_fill_chroma_sample_location(props);
    vaapi_vpp_fill_colour_range(props);

    av_log(avctx, AV_LOG_DEBUG, "Mapped colour properties %s %s/%s/%s %s "
           "to VA standard %d chroma siting %#x range %#x.\n",
           av_color_range_name(props->color_range),
           av_color_space_name(props->colorspace),
           av_color_primaries_name(props->color_primaries),
           av_color_transfer_name(props->color_trc),
           av_chroma_location_name(props->chroma_sample_location),
           props->va_color_standard,
           props->va_chroma_sample_location, props->va_color_range);
}