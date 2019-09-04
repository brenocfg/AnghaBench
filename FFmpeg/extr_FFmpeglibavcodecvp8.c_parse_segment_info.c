#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {void* update_map; void** filter_level; void** base_quant; void* absolute_vals; void* update_feature_data; } ;
struct TYPE_7__ {TYPE_2__* prob; TYPE_1__ segmentation; int /*<<< orphan*/  c; } ;
typedef  TYPE_3__ VP8Context ;
typedef  int /*<<< orphan*/  VP56RangeCoder ;
struct TYPE_6__ {int* segmentid; } ;

/* Variables and functions */
 void* vp8_rac_get (int /*<<< orphan*/ *) ; 
 void* vp8_rac_get_sint (int /*<<< orphan*/ *,int) ; 
 int vp8_rac_get_uint (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void parse_segment_info(VP8Context *s)
{
    VP56RangeCoder *c = &s->c;
    int i;

    s->segmentation.update_map = vp8_rac_get(c);
    s->segmentation.update_feature_data = vp8_rac_get(c);

    if (s->segmentation.update_feature_data) {
        s->segmentation.absolute_vals = vp8_rac_get(c);

        for (i = 0; i < 4; i++)
            s->segmentation.base_quant[i]   = vp8_rac_get_sint(c, 7);

        for (i = 0; i < 4; i++)
            s->segmentation.filter_level[i] = vp8_rac_get_sint(c, 6);
    }
    if (s->segmentation.update_map)
        for (i = 0; i < 3; i++)
            s->prob->segmentid[i] = vp8_rac_get(c) ? vp8_rac_get_uint(c, 8) : 255;
}