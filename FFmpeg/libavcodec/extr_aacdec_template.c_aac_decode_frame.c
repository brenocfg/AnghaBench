#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct TYPE_17__ {int object_type; } ;
struct TYPE_16__ {scalar_t__ dmono_mode; scalar_t__ force_dmono_mode; TYPE_1__* oc; int /*<<< orphan*/  avctx; } ;
struct TYPE_15__ {TYPE_4__* priv_data; } ;
struct TYPE_14__ {scalar_t__* data; int size; } ;
struct TYPE_13__ {TYPE_6__ m4ac; int /*<<< orphan*/  status; } ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVCodecContext ;
typedef  TYPE_4__ AACContext ;

/* Variables and functions */
#define  AOT_ER_AAC_ELD 131 
#define  AOT_ER_AAC_LC 130 
#define  AOT_ER_AAC_LD 129 
#define  AOT_ER_AAC_LTP 128 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_PKT_DATA_JP_DUALMONO ; 
 int /*<<< orphan*/  AV_PKT_DATA_NEW_EXTRADATA ; 
 int INT_MAX ; 
 int /*<<< orphan*/  OC_NONE ; 
 int aac_decode_er_frame (TYPE_3__*,void*,int*,int /*<<< orphan*/ *) ; 
 int aac_decode_frame_int (TYPE_3__*,void*,int*,int /*<<< orphan*/ *,TYPE_2__*) ; 
 scalar_t__* av_packet_get_side_data (TYPE_2__*,int /*<<< orphan*/ ,int*) ; 
 int decode_audio_specific_config (TYPE_4__*,int /*<<< orphan*/ ,TYPE_6__*,scalar_t__ const*,int,int) ; 
 int get_bits_count (int /*<<< orphan*/ *) ; 
 int init_get_bits8 (int /*<<< orphan*/ *,scalar_t__ const*,int) ; 

__attribute__((used)) static int aac_decode_frame(AVCodecContext *avctx, void *data,
                            int *got_frame_ptr, AVPacket *avpkt)
{
    AACContext *ac = avctx->priv_data;
    const uint8_t *buf = avpkt->data;
    int buf_size = avpkt->size;
    GetBitContext gb;
    int buf_consumed;
    int buf_offset;
    int err;
    int new_extradata_size;
    const uint8_t *new_extradata = av_packet_get_side_data(avpkt,
                                       AV_PKT_DATA_NEW_EXTRADATA,
                                       &new_extradata_size);
    int jp_dualmono_size;
    const uint8_t *jp_dualmono   = av_packet_get_side_data(avpkt,
                                       AV_PKT_DATA_JP_DUALMONO,
                                       &jp_dualmono_size);

    if (new_extradata) {
        /* discard previous configuration */
        ac->oc[1].status = OC_NONE;
        err = decode_audio_specific_config(ac, ac->avctx, &ac->oc[1].m4ac,
                                           new_extradata,
                                           new_extradata_size * 8LL, 1);
        if (err < 0) {
            return err;
        }
    }

    ac->dmono_mode = 0;
    if (jp_dualmono && jp_dualmono_size > 0)
        ac->dmono_mode =  1 + *jp_dualmono;
    if (ac->force_dmono_mode >= 0)
        ac->dmono_mode = ac->force_dmono_mode;

    if (INT_MAX / 8 <= buf_size)
        return AVERROR_INVALIDDATA;

    if ((err = init_get_bits8(&gb, buf, buf_size)) < 0)
        return err;

    switch (ac->oc[1].m4ac.object_type) {
    case AOT_ER_AAC_LC:
    case AOT_ER_AAC_LTP:
    case AOT_ER_AAC_LD:
    case AOT_ER_AAC_ELD:
        err = aac_decode_er_frame(avctx, data, got_frame_ptr, &gb);
        break;
    default:
        err = aac_decode_frame_int(avctx, data, got_frame_ptr, &gb, avpkt);
    }
    if (err < 0)
        return err;

    buf_consumed = (get_bits_count(&gb) + 7) >> 3;
    for (buf_offset = buf_consumed; buf_offset < buf_size; buf_offset++)
        if (buf[buf_offset])
            break;

    return buf_size > buf_offset ? buf_consumed : buf_size;
}