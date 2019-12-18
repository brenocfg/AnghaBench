#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int int64_t ;
struct TYPE_17__ {int interlaced; int /*<<< orphan*/  pb; TYPE_4__* avctx; TYPE_5__* transform_args; int /*<<< orphan*/ * plane; } ;
typedef  TYPE_1__ VC2EncContext ;
typedef  int /*<<< orphan*/  TransformArgs ;
struct TYPE_21__ {int field; int /*<<< orphan*/  istride; int /*<<< orphan*/  idata; int /*<<< orphan*/ * plane; TYPE_1__* ctx; } ;
struct TYPE_20__ {int /*<<< orphan*/  (* execute ) (TYPE_4__*,int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ *,int,int) ;} ;
struct TYPE_19__ {int /*<<< orphan*/ * linesize; int /*<<< orphan*/ * data; } ;
struct TYPE_18__ {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVFrame ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  DIRAC_PCODE_AUX ; 
 int /*<<< orphan*/  DIRAC_PCODE_END_SEQ ; 
 int /*<<< orphan*/  DIRAC_PCODE_PICTURE_HQ ; 
 int /*<<< orphan*/  DIRAC_PCODE_SEQ_HEADER ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  avpriv_put_string (int /*<<< orphan*/ *,char const*,int) ; 
 int calc_slice_sizes (TYPE_1__*) ; 
 int /*<<< orphan*/  dwt_plane ; 
 int /*<<< orphan*/  encode_parse_info (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  encode_picture_start (TYPE_1__*) ; 
 int /*<<< orphan*/  encode_seq_header (TYPE_1__*) ; 
 int /*<<< orphan*/  encode_slices (TYPE_1__*) ; 
 int ff_alloc_packet2 (TYPE_4__*,TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  init_put_bits (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int encode_frame(VC2EncContext *s, AVPacket *avpkt, const AVFrame *frame,
                        const char *aux_data, const int header_size, int field)
{
    int i, ret;
    int64_t max_frame_bytes;

     /* Threaded DWT transform */
    for (i = 0; i < 3; i++) {
        s->transform_args[i].ctx   = s;
        s->transform_args[i].field = field;
        s->transform_args[i].plane = &s->plane[i];
        s->transform_args[i].idata = frame->data[i];
        s->transform_args[i].istride = frame->linesize[i];
    }
    s->avctx->execute(s->avctx, dwt_plane, s->transform_args, NULL, 3,
                      sizeof(TransformArgs));

    /* Calculate per-slice quantizers and sizes */
    max_frame_bytes = header_size + calc_slice_sizes(s);

    if (field < 2) {
        ret = ff_alloc_packet2(s->avctx, avpkt,
                               max_frame_bytes << s->interlaced,
                               max_frame_bytes << s->interlaced);
        if (ret) {
            av_log(s->avctx, AV_LOG_ERROR, "Error getting output packet.\n");
            return ret;
        }
        init_put_bits(&s->pb, avpkt->data, avpkt->size);
    }

    /* Sequence header */
    encode_parse_info(s, DIRAC_PCODE_SEQ_HEADER);
    encode_seq_header(s);

    /* Encoder version */
    if (aux_data) {
        encode_parse_info(s, DIRAC_PCODE_AUX);
        avpriv_put_string(&s->pb, aux_data, 1);
    }

    /* Picture header */
    encode_parse_info(s, DIRAC_PCODE_PICTURE_HQ);
    encode_picture_start(s);

    /* Encode slices */
    encode_slices(s);

    /* End sequence */
    encode_parse_info(s, DIRAC_PCODE_END_SEQ);

    return 0;
}