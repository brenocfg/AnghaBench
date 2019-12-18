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
struct TYPE_8__ {TYPE_5__** vps_list; TYPE_6__** sps_list; int /*<<< orphan*/  const* vps; } ;
struct TYPE_7__ {int vps_id; } ;
typedef  int /*<<< orphan*/  HEVCVPS ;
typedef  TYPE_1__ HEVCSPS ;
typedef  TYPE_2__ HEVCParamSets ;

/* Variables and functions */
 int FF_ARRAY_ELEMS (TYPE_6__**) ; 
 int /*<<< orphan*/  av_buffer_unref (TYPE_5__**) ; 
 int /*<<< orphan*/  remove_sps (TYPE_2__*,int) ; 

__attribute__((used)) static void remove_vps(HEVCParamSets *s, int id)
{
    int i;
    if (s->vps_list[id]) {
        if (s->vps == (const HEVCVPS*)s->vps_list[id]->data)
            s->vps = NULL;

        for (i = 0; i < FF_ARRAY_ELEMS(s->sps_list); i++)
            if (s->sps_list[i] && ((HEVCSPS*)s->sps_list[i]->data)->vps_id == id)
                remove_sps(s, i);
    }
    av_buffer_unref(&s->vps_list[id]);
}