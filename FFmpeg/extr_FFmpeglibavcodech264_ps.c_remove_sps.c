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
struct TYPE_3__ {int /*<<< orphan*/ * sps_list; } ;
typedef  TYPE_1__ H264ParamSets ;

/* Variables and functions */
 int /*<<< orphan*/  av_buffer_unref (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void remove_sps(H264ParamSets *s, int id)
{
#if 0
    int i;
    if (s->sps_list[id]) {
        /* drop all PPS that depend on this SPS */
        for (i = 0; i < FF_ARRAY_ELEMS(s->pps_list); i++)
            if (s->pps_list[i] && ((PPS*)s->pps_list[i]->data)->sps_id == id)
                remove_pps(s, i);
    }
#endif
    av_buffer_unref(&s->sps_list[id]);
}