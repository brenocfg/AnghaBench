#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT32 ;
struct TYPE_2__ {int divisor; int (* filter ) (void*,void*,int,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ;int (* nofilter ) (void*,void*,int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  src_sps; int /*<<< orphan*/  overlap_area; int /*<<< orphan*/  cur_pos; scalar_t__ can_be_filtered; } ;
typedef  int INT32 ;

/* Variables and functions */
 int /*<<< orphan*/  APPL_TRACE_DEBUG (char*,int) ; 
 TYPE_1__* p_bta_dm_pcm_cb ; 
 int stub1 (void*,void*,int,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int stub2 (void*,void*,int,int /*<<< orphan*/ ) ; 

INT32 BTA_DmPcmResample (void *p_src, UINT32 in_bytes, void *p_dst)
{
    UINT32 out_sample;

#if BTA_DM_SCO_DEBUG
    APPL_TRACE_DEBUG("bta_pcm_resample : insamples  %d",  (in_bytes  / p_bta_dm_pcm_cb->divisor));
#endif
    if (p_bta_dm_pcm_cb->can_be_filtered) {
        out_sample = (*p_bta_dm_pcm_cb->filter) (p_src, p_dst, (in_bytes  / p_bta_dm_pcm_cb->divisor),
                                              p_bta_dm_pcm_cb->src_sps, (INT32 *) &(p_bta_dm_pcm_cb->cur_pos), p_bta_dm_pcm_cb->overlap_area);
    } else {
        out_sample = (*p_bta_dm_pcm_cb->nofilter) (p_src, p_dst,
                                                (in_bytes / p_bta_dm_pcm_cb->divisor), p_bta_dm_pcm_cb->src_sps);
    }

#if BTA_DM_SCO_DEBUG
    APPL_TRACE_DEBUG("bta_pcm_resample : outsamples  %d",  out_sample);
#endif

    return (out_sample);
}