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
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_17__ {int nb_obus; TYPE_5__* obus; } ;
struct TYPE_16__ {int const type; scalar_t__ raw_size; int /*<<< orphan*/  raw_data; } ;
struct TYPE_15__ {TYPE_1__* priv_data; } ;
struct TYPE_14__ {int /*<<< orphan*/ * data; } ;
struct TYPE_13__ {int size; int /*<<< orphan*/ * data; TYPE_3__* buf; } ;
struct TYPE_12__ {scalar_t__ remove; TYPE_6__ av1_pkt; } ;
typedef  TYPE_1__ ExtractExtradataContext ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVBufferRef ;
typedef  TYPE_4__ AVBSFContext ;
typedef  TYPE_5__ AV1OBU ;

/* Variables and functions */
#define  AV1_OBU_METADATA 129 
#define  AV1_OBU_SEQUENCE_HEADER 128 
 int AVERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ AV_INPUT_BUFFER_PADDING_SIZE ; 
 int /*<<< orphan*/  ENOMEM ; 
 int FF_ARRAY_ELEMS (int const*) ; 
 TYPE_3__* av_buffer_alloc (scalar_t__) ; 
 int /*<<< orphan*/  av_buffer_unref (TYPE_3__**) ; 
 int /*<<< orphan*/ * av_malloc (scalar_t__) ; 
 int ff_av1_packet_split (TYPE_6__*,int /*<<< orphan*/ *,int,TYPE_4__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ val_in_array (int const*,int,int const) ; 

__attribute__((used)) static int extract_extradata_av1(AVBSFContext *ctx, AVPacket *pkt,
                                 uint8_t **data, int *size)
{
    static const int extradata_obu_types[] = {
        AV1_OBU_SEQUENCE_HEADER, AV1_OBU_METADATA,
    };
    ExtractExtradataContext *s = ctx->priv_data;

    int extradata_size = 0, filtered_size = 0;
    int nb_extradata_obu_types = FF_ARRAY_ELEMS(extradata_obu_types);
    int i, has_seq = 0, ret = 0;

    ret = ff_av1_packet_split(&s->av1_pkt, pkt->data, pkt->size, ctx);
    if (ret < 0)
        return ret;

    for (i = 0; i < s->av1_pkt.nb_obus; i++) {
        AV1OBU *obu = &s->av1_pkt.obus[i];
        if (val_in_array(extradata_obu_types, nb_extradata_obu_types, obu->type)) {
            extradata_size += obu->raw_size;
            if (obu->type == AV1_OBU_SEQUENCE_HEADER)
                has_seq = 1;
        } else if (s->remove) {
            filtered_size += obu->raw_size;
        }
    }

    if (extradata_size && has_seq) {
        AVBufferRef *filtered_buf;
        uint8_t *extradata, *filtered_data;

        if (s->remove) {
            filtered_buf = av_buffer_alloc(filtered_size + AV_INPUT_BUFFER_PADDING_SIZE);
            if (!filtered_buf) {
                return AVERROR(ENOMEM);
            }
            memset(filtered_buf->data + filtered_size, 0, AV_INPUT_BUFFER_PADDING_SIZE);

            filtered_data = filtered_buf->data;
        }

        extradata = av_malloc(extradata_size + AV_INPUT_BUFFER_PADDING_SIZE);
        if (!extradata) {
            av_buffer_unref(&filtered_buf);
            return AVERROR(ENOMEM);
        }
        memset(extradata + extradata_size, 0, AV_INPUT_BUFFER_PADDING_SIZE);

        *data = extradata;
        *size = extradata_size;

        for (i = 0; i < s->av1_pkt.nb_obus; i++) {
            AV1OBU *obu = &s->av1_pkt.obus[i];
            if (val_in_array(extradata_obu_types, nb_extradata_obu_types,
                             obu->type)) {
                memcpy(extradata, obu->raw_data, obu->raw_size);
                extradata += obu->raw_size;
            } else if (s->remove) {
                memcpy(filtered_data, obu->raw_data, obu->raw_size);
                filtered_data += obu->raw_size;
            }
        }

        if (s->remove) {
            av_buffer_unref(&pkt->buf);
            pkt->buf  = filtered_buf;
            pkt->data = filtered_buf->data;
            pkt->size = filtered_size;
        }
    }

    return 0;
}