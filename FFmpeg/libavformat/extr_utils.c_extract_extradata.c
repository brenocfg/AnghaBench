#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_10__ {TYPE_3__* internal; } ;
struct TYPE_7__ {int /*<<< orphan*/  bsf; int /*<<< orphan*/ * pkt; scalar_t__ inited; } ;
struct TYPE_9__ {TYPE_2__* avctx; TYPE_1__ extract_extradata; } ;
struct TYPE_8__ {int extradata_size; scalar_t__ extradata; } ;
typedef  TYPE_3__ AVStreamInternal ;
typedef  TYPE_4__ AVStream ;
typedef  int /*<<< orphan*/  AVPacket ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EOF ; 
 scalar_t__ AV_INPUT_BUFFER_PADDING_SIZE ; 
 int /*<<< orphan*/  AV_PKT_DATA_NEW_EXTRADATA ; 
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  ENOMEM ; 
 unsigned int FF_MAX_EXTRADATA_SIZE ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int av_bsf_receive_packet (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int av_bsf_send_packet (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ av_mallocz (scalar_t__) ; 
 int /*<<< orphan*/ * av_packet_get_side_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int av_packet_ref (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  av_packet_unref (int /*<<< orphan*/ *) ; 
 int extract_extradata_init (TYPE_4__*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int extract_extradata(AVStream *st, const AVPacket *pkt)
{
    AVStreamInternal *sti = st->internal;
    AVPacket *pkt_ref;
    int ret;

    if (!sti->extract_extradata.inited) {
        ret = extract_extradata_init(st);
        if (ret < 0)
            return ret;
    }

    if (sti->extract_extradata.inited && !sti->extract_extradata.bsf)
        return 0;

    pkt_ref = sti->extract_extradata.pkt;
    ret = av_packet_ref(pkt_ref, pkt);
    if (ret < 0)
        return ret;

    ret = av_bsf_send_packet(sti->extract_extradata.bsf, pkt_ref);
    if (ret < 0) {
        av_packet_unref(pkt_ref);
        return ret;
    }

    while (ret >= 0 && !sti->avctx->extradata) {
        int extradata_size;
        uint8_t *extradata;

        ret = av_bsf_receive_packet(sti->extract_extradata.bsf, pkt_ref);
        if (ret < 0) {
            if (ret != AVERROR(EAGAIN) && ret != AVERROR_EOF)
                return ret;
            continue;
        }

        extradata = av_packet_get_side_data(pkt_ref, AV_PKT_DATA_NEW_EXTRADATA,
                                            &extradata_size);

        if (extradata) {
            av_assert0(!sti->avctx->extradata);
            if ((unsigned)extradata_size < FF_MAX_EXTRADATA_SIZE)
                sti->avctx->extradata = av_mallocz(extradata_size + AV_INPUT_BUFFER_PADDING_SIZE);
            if (!sti->avctx->extradata) {
                av_packet_unref(pkt_ref);
                return AVERROR(ENOMEM);
            }
            memcpy(sti->avctx->extradata, extradata, extradata_size);
            sti->avctx->extradata_size = extradata_size;
        }
        av_packet_unref(pkt_ref);
    }

    return 0;
}