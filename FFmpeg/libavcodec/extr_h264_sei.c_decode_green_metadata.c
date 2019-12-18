#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int green_metadata_type; int period_type; void* xsd_metric_value; void* xsd_metric_type; void* percent_alpha_point_deblocking_instance; void* percent_six_tap_filtering; void* percent_intra_coded_macroblocks; void* percent_non_zero_macroblocks; void* num_pictures; void* num_seconds; } ;
typedef  TYPE_1__ H264SEIGreenMetaData ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 void* get_bits (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int decode_green_metadata(H264SEIGreenMetaData *h, GetBitContext *gb)
{
    h->green_metadata_type = get_bits(gb, 8);

    if (h->green_metadata_type == 0) {
        h->period_type = get_bits(gb, 8);

        if (h->period_type == 2)
            h->num_seconds = get_bits(gb, 16);
        else if (h->period_type == 3)
            h->num_pictures = get_bits(gb, 16);

        h->percent_non_zero_macroblocks            = get_bits(gb, 8);
        h->percent_intra_coded_macroblocks         = get_bits(gb, 8);
        h->percent_six_tap_filtering               = get_bits(gb, 8);
        h->percent_alpha_point_deblocking_instance = get_bits(gb, 8);

    } else if (h->green_metadata_type == 1) {
        h->xsd_metric_type  = get_bits(gb, 8);
        h->xsd_metric_value = get_bits(gb, 16);
    }

    return 0;
}