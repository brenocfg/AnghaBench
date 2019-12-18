#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ data; } ;
struct TYPE_7__ {scalar_t__* sps_list; TYPE_5__** pps_list; } ;
struct TYPE_6__ {int sps_id; } ;
typedef  TYPE_1__ PPS ;
typedef  TYPE_2__ H264ParamSets ;

/* Variables and functions */
 int FF_ARRAY_ELEMS (TYPE_5__**) ; 
 int /*<<< orphan*/  av_buffer_unref (scalar_t__*) ; 
 int /*<<< orphan*/  remove_pps (TYPE_2__*,int) ; 

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