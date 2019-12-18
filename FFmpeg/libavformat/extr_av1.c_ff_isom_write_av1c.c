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
typedef  int /*<<< orphan*/  const uint8_t ;
typedef  int /*<<< orphan*/  int64_t ;
typedef  int /*<<< orphan*/  header ;
struct TYPE_3__ {int profile; int level; int tier; int bitdepth; int monochrome; int chroma_subsampling_x; int chroma_subsampling_y; int chroma_sample_position; } ;
typedef  int /*<<< orphan*/  PutBitContext ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_1__ AV1SequenceParameters ;

/* Variables and functions */
#define  AV1_OBU_METADATA 129 
#define  AV1_OBU_SEQUENCE_HEADER 128 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  av_free (int /*<<< orphan*/  const*) ; 
 int avio_close_dyn_buf (int /*<<< orphan*/ *,int /*<<< orphan*/  const**) ; 
 int avio_open_dyn_buf (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  flush_put_bits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_put_bits (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int parse_obu_header (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *,int*,int*,int*,int*) ; 
 int parse_sequence_header (TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_bits (int /*<<< orphan*/ *,int,int) ; 

int ff_isom_write_av1c(AVIOContext *pb, const uint8_t *buf, int size)
{
    AVIOContext *seq_pb = NULL, *meta_pb = NULL;
    AV1SequenceParameters seq_params;
    PutBitContext pbc;
    uint8_t header[4];
    uint8_t *seq = NULL, *meta = NULL;
    int64_t obu_size;
    int start_pos, type, temporal_id, spatial_id;
    int ret, nb_seq = 0, seq_size, meta_size;

    if (size <= 0)
        return AVERROR_INVALIDDATA;

    ret = avio_open_dyn_buf(&seq_pb);
    if (ret < 0)
        return ret;
    ret = avio_open_dyn_buf(&meta_pb);
    if (ret < 0)
        goto fail;

    while (size > 0) {
        int len = parse_obu_header(buf, size, &obu_size, &start_pos,
                                   &type, &temporal_id, &spatial_id);
        if (len < 0) {
            ret = len;
            goto fail;
        }

        switch (type) {
        case AV1_OBU_SEQUENCE_HEADER:
            nb_seq++;
            if (!obu_size || nb_seq > 1) {
                ret = AVERROR_INVALIDDATA;
                goto fail;
            }
            ret = parse_sequence_header(&seq_params, buf + start_pos, obu_size);
            if (ret < 0)
                goto fail;

            avio_write(seq_pb, buf, len);
            break;
        case AV1_OBU_METADATA:
            if (!obu_size) {
                ret = AVERROR_INVALIDDATA;
                goto fail;
            }
            avio_write(meta_pb, buf, len);
            break;
        default:
            break;
        }
        size -= len;
        buf  += len;
    }

    seq_size  = avio_close_dyn_buf(seq_pb, &seq);
    if (!seq_size) {
        ret = AVERROR_INVALIDDATA;
        goto fail;
    }

    init_put_bits(&pbc, header, sizeof(header));

    put_bits(&pbc, 1, 1); // marker
    put_bits(&pbc, 7, 1); // version
    put_bits(&pbc, 3, seq_params.profile);
    put_bits(&pbc, 5, seq_params.level);
    put_bits(&pbc, 1, seq_params.tier);
    put_bits(&pbc, 1, seq_params.bitdepth > 8);
    put_bits(&pbc, 1, seq_params.bitdepth == 12);
    put_bits(&pbc, 1, seq_params.monochrome);
    put_bits(&pbc, 1, seq_params.chroma_subsampling_x);
    put_bits(&pbc, 1, seq_params.chroma_subsampling_y);
    put_bits(&pbc, 2, seq_params.chroma_sample_position);
    put_bits(&pbc, 8, 0); // padding
    flush_put_bits(&pbc);

    avio_write(pb, header, sizeof(header));
    avio_write(pb, seq, seq_size);

    meta_size = avio_close_dyn_buf(meta_pb, &meta);
    if (meta_size)
        avio_write(pb, meta, meta_size);

fail:
    if (!seq)
        avio_close_dyn_buf(seq_pb, &seq);
    if (!meta)
        avio_close_dyn_buf(meta_pb, &meta);
    av_free(seq);
    av_free(meta);

    return ret;
}