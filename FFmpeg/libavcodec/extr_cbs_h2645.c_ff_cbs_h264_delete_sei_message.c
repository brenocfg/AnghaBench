#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int nb_units; TYPE_2__* units; } ;
struct TYPE_8__ {scalar_t__ type; TYPE_1__* content; } ;
struct TYPE_7__ {int payload_count; int /*<<< orphan*/ * payload; } ;
typedef  TYPE_1__ H264RawSEI ;
typedef  TYPE_2__ CodedBitstreamUnit ;
typedef  TYPE_3__ CodedBitstreamFragment ;
typedef  int /*<<< orphan*/  CodedBitstreamContext ;

/* Variables and functions */
 scalar_t__ H264_NAL_SEI ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int /*<<< orphan*/  cbs_h264_free_sei_payload (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_cbs_delete_unit (int /*<<< orphan*/ *,TYPE_3__*,int) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

void ff_cbs_h264_delete_sei_message(CodedBitstreamContext *ctx,
                                    CodedBitstreamFragment *au,
                                    CodedBitstreamUnit *nal,
                                    int position)
{
    H264RawSEI *sei = nal->content;

    av_assert0(nal->type == H264_NAL_SEI);
    av_assert0(position >= 0 && position < sei->payload_count);

    if (position == 0 && sei->payload_count == 1) {
        // Deleting NAL unit entirely.
        int i;

        for (i = 0; i < au->nb_units; i++) {
            if (&au->units[i] == nal)
                break;
        }

        ff_cbs_delete_unit(ctx, au, i);
    } else {
        cbs_h264_free_sei_payload(&sei->payload[position]);

        --sei->payload_count;
        memmove(sei->payload + position,
                sei->payload + position + 1,
                (sei->payload_count - position) * sizeof(*sei->payload));
    }
}