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
struct TYPE_3__ {int /*<<< orphan*/ * vps; int /*<<< orphan*/ * pps; int /*<<< orphan*/ * sps; int /*<<< orphan*/ * pps_list; int /*<<< orphan*/ * sps_list; int /*<<< orphan*/ * vps_list; } ;
typedef  TYPE_1__ HEVCParamSets ;

/* Variables and functions */
 int FF_ARRAY_ELEMS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_buffer_unref (int /*<<< orphan*/ *) ; 

void ff_hevc_ps_uninit(HEVCParamSets *ps)
{
    int i;

    for (i = 0; i < FF_ARRAY_ELEMS(ps->vps_list); i++)
        av_buffer_unref(&ps->vps_list[i]);
    for (i = 0; i < FF_ARRAY_ELEMS(ps->sps_list); i++)
        av_buffer_unref(&ps->sps_list[i]);
    for (i = 0; i < FF_ARRAY_ELEMS(ps->pps_list); i++)
        av_buffer_unref(&ps->pps_list[i]);

    ps->sps = NULL;
    ps->pps = NULL;
    ps->vps = NULL;
}