#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_18__ {int /*<<< orphan*/  log_ctx; } ;
struct TYPE_17__ {int nb_units; TYPE_3__* units; } ;
struct TYPE_16__ {scalar_t__ type; TYPE_2__* content; } ;
struct TYPE_14__ {scalar_t__ nal_ref_idc; scalar_t__ nal_unit_type; } ;
struct TYPE_15__ {size_t payload_count; int /*<<< orphan*/ * payload; TYPE_1__ nal_unit_header; } ;
typedef  int /*<<< orphan*/  H264RawSEIPayload ;
typedef  TYPE_2__ H264RawSEI ;
typedef  TYPE_3__ CodedBitstreamUnit ;
typedef  TYPE_4__ CodedBitstreamFragment ;
typedef  TYPE_5__ CodedBitstreamContext ;
typedef  int /*<<< orphan*/  AVBufferRef ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 size_t H264_MAX_SEI_PAYLOADS ; 
 scalar_t__ H264_NAL_IDR_SLICE ; 
 scalar_t__ H264_NAL_SEI ; 
 scalar_t__ H264_NAL_SLICE ; 
 int /*<<< orphan*/ * av_buffer_create (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_buffer_unref (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  av_freep (TYPE_2__**) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 TYPE_2__* av_mallocz (int) ; 
 int /*<<< orphan*/  cbs_h264_free_sei ; 
 int ff_cbs_insert_unit_content (TYPE_5__*,TYPE_4__*,int,scalar_t__,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

int ff_cbs_h264_add_sei_message(CodedBitstreamContext *ctx,
                                CodedBitstreamFragment *au,
                                const H264RawSEIPayload *payload)
{
    H264RawSEI *sei;
    CodedBitstreamUnit *nal = NULL;
    int err, i;

    // Find an existing SEI NAL unit to add to.
    for (i = 0; i < au->nb_units; i++) {
        if (au->units[i].type == H264_NAL_SEI) {
            nal = &au->units[i];
            break;
        }
    }
    if (nal) {
        sei = nal->content;

    } else {
        // Need to make a new SEI NAL unit.  Insert it before the first
        // slice data NAL unit; if no slice data, add at the end.
        AVBufferRef *sei_ref;

        sei = av_mallocz(sizeof(*sei));
        if (!sei)
            return AVERROR(ENOMEM);

        sei->nal_unit_header.nal_unit_type = H264_NAL_SEI;
        sei->nal_unit_header.nal_ref_idc   = 0;

        sei_ref = av_buffer_create((uint8_t*)sei, sizeof(*sei),
                                   &cbs_h264_free_sei, ctx, 0);
        if (!sei_ref) {
            av_freep(&sei);
            return AVERROR(ENOMEM);
        }

        for (i = 0; i < au->nb_units; i++) {
            if (au->units[i].type == H264_NAL_SLICE ||
                au->units[i].type == H264_NAL_IDR_SLICE)
                break;
        }

        err = ff_cbs_insert_unit_content(ctx, au, i, H264_NAL_SEI,
                                         sei, sei_ref);
        av_buffer_unref(&sei_ref);
        if (err < 0)
            return err;
    }

    if (sei->payload_count >= H264_MAX_SEI_PAYLOADS) {
        av_log(ctx->log_ctx, AV_LOG_ERROR, "Too many payloads in "
               "SEI NAL unit.\n");
        return AVERROR(EINVAL);
    }

    memcpy(&sei->payload[sei->payload_count], payload, sizeof(*payload));
    ++sei->payload_count;

    return 0;
}