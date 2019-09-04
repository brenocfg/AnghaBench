#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_1__* sps; } ;
struct TYPE_14__ {scalar_t__ seq_decode; scalar_t__ nal_unit_type; int /*<<< orphan*/  avctx; TYPE_4__* DPB; TYPE_2__ ps; } ;
struct TYPE_13__ {scalar_t__ sequence; int poc; TYPE_3__* frame; } ;
struct TYPE_12__ {scalar_t__* buf; } ;
struct TYPE_10__ {int log2_max_poc_lsb; } ;
typedef  TYPE_4__ HEVCFrame ;
typedef  TYPE_5__ HEVCContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int FF_ARRAY_ELEMS (TYPE_4__*) ; 
 scalar_t__ HEVC_NAL_CRA_NUT ; 
 int /*<<< orphan*/  IS_BLA (TYPE_5__*) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static HEVCFrame *find_ref_idx(HEVCContext *s, int poc)
{
    int i;
    int LtMask = (1 << s->ps.sps->log2_max_poc_lsb) - 1;

    for (i = 0; i < FF_ARRAY_ELEMS(s->DPB); i++) {
        HEVCFrame *ref = &s->DPB[i];
        if (ref->frame->buf[0] && (ref->sequence == s->seq_decode)) {
            if ((ref->poc & LtMask) == poc)
                return ref;
        }
    }

    for (i = 0; i < FF_ARRAY_ELEMS(s->DPB); i++) {
        HEVCFrame *ref = &s->DPB[i];
        if (ref->frame->buf[0] && ref->sequence == s->seq_decode) {
            if (ref->poc == poc || (ref->poc & LtMask) == poc)
                return ref;
        }
    }

    if (s->nal_unit_type != HEVC_NAL_CRA_NUT && !IS_BLA(s))
        av_log(s->avctx, AV_LOG_ERROR,
               "Could not find ref with POC %d\n", poc);
    return NULL;
}