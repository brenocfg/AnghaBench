#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ data; } ;
struct TYPE_9__ {scalar_t__ data; } ;
struct TYPE_8__ {int sps_id; } ;
struct TYPE_7__ {TYPE_5__** sps_list; int /*<<< orphan*/  const* sps; TYPE_6__** pps_list; } ;
typedef  int /*<<< orphan*/  const HEVCSPS ;
typedef  TYPE_1__ HEVCParamSets ;
typedef  TYPE_2__ HEVCPPS ;

/* Variables and functions */
 int FF_ARRAY_ELEMS (TYPE_6__**) ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int /*<<< orphan*/  av_buffer_unref (TYPE_5__**) ; 
 int /*<<< orphan*/  remove_pps (TYPE_1__*,int) ; 

__attribute__((used)) static void remove_sps(HEVCParamSets *s, int id)
{
    int i;
    if (s->sps_list[id]) {
        if (s->sps == (const HEVCSPS*)s->sps_list[id]->data)
            s->sps = NULL;

        /* drop all PPS that depend on this SPS */
        for (i = 0; i < FF_ARRAY_ELEMS(s->pps_list); i++)
            if (s->pps_list[i] && ((HEVCPPS*)s->pps_list[i]->data)->sps_id == id)
                remove_pps(s, i);

        av_assert0(!(s->sps_list[id] && s->sps == (HEVCSPS*)s->sps_list[id]->data));
    }
    av_buffer_unref(&s->sps_list[id]);
}