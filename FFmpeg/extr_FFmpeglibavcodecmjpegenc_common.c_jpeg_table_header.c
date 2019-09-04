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
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  luma_intra_matrix ;
struct TYPE_10__ {scalar_t__ codec_id; int active_thread_type; int width; TYPE_3__* priv_data; } ;
struct TYPE_9__ {scalar_t__ huffman; TYPE_1__* mjpeg_ctx; scalar_t__ force_duplicated_matrix; } ;
struct TYPE_8__ {int* permutated; } ;
struct TYPE_7__ {int /*<<< orphan*/  val_ac_chrominance; int /*<<< orphan*/  bits_ac_chrominance; int /*<<< orphan*/  val_ac_luminance; int /*<<< orphan*/  bits_ac_luminance; int /*<<< orphan*/  val_dc_chrominance; int /*<<< orphan*/  bits_dc_chrominance; int /*<<< orphan*/  val_dc_luminance; int /*<<< orphan*/  bits_dc_luminance; } ;
typedef  TYPE_2__ ScanTable ;
typedef  int /*<<< orphan*/  PutBitContext ;
typedef  TYPE_3__ MpegEncContext ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 scalar_t__ AV_CODEC_ID_LJPEG ; 
 int /*<<< orphan*/  AV_WB16 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  DHT ; 
 int /*<<< orphan*/  DQT ; 
 int /*<<< orphan*/  DRI ; 
 int FF_THREAD_SLICE ; 
 scalar_t__ HUFFMAN_TABLE_OPTIMAL ; 
 int /*<<< orphan*/  avpriv_mjpeg_bits_ac_chrominance ; 
 int /*<<< orphan*/  avpriv_mjpeg_bits_ac_luminance ; 
 int /*<<< orphan*/  avpriv_mjpeg_bits_dc_chrominance ; 
 int /*<<< orphan*/  avpriv_mjpeg_bits_dc_luminance ; 
 int /*<<< orphan*/  avpriv_mjpeg_val_ac_chrominance ; 
 int /*<<< orphan*/  avpriv_mjpeg_val_ac_luminance ; 
 int /*<<< orphan*/  avpriv_mjpeg_val_dc ; 
 int /*<<< orphan*/  flush_put_bits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcmp (int*,int*,int) ; 
 int /*<<< orphan*/  put_bits (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/ * put_bits_ptr (int /*<<< orphan*/ *) ; 
 scalar_t__ put_huffman_table (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_marker (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void jpeg_table_header(AVCodecContext *avctx, PutBitContext *p,
                              ScanTable *intra_scantable,
                              uint16_t luma_intra_matrix[64],
                              uint16_t chroma_intra_matrix[64],
                              int hsample[3])
{
    int i, j, size;
    uint8_t *ptr;
    MpegEncContext *s = NULL;

    /* Since avctx->priv_data will point to LJpegEncContext in this case */
    if (avctx->codec_id != AV_CODEC_ID_LJPEG)
        s = avctx->priv_data;

    if (avctx->codec_id != AV_CODEC_ID_LJPEG) {
        int matrix_count = 1 + !!memcmp(luma_intra_matrix,
                                        chroma_intra_matrix,
                                        sizeof(luma_intra_matrix[0]) * 64);
    if (s && s->force_duplicated_matrix)
        matrix_count = 2;
    /* quant matrixes */
    put_marker(p, DQT);
    put_bits(p, 16, 2 + matrix_count * (1 + 64));
    put_bits(p, 4, 0); /* 8 bit precision */
    put_bits(p, 4, 0); /* table 0 */
    for(i=0;i<64;i++) {
        j = intra_scantable->permutated[i];
        put_bits(p, 8, luma_intra_matrix[j]);
    }

        if (matrix_count > 1) {
            put_bits(p, 4, 0); /* 8 bit precision */
            put_bits(p, 4, 1); /* table 1 */
            for(i=0;i<64;i++) {
                j = intra_scantable->permutated[i];
                put_bits(p, 8, chroma_intra_matrix[j]);
            }
        }
    }

    if(avctx->active_thread_type & FF_THREAD_SLICE){
        put_marker(p, DRI);
        put_bits(p, 16, 4);
        put_bits(p, 16, (avctx->width-1)/(8*hsample[0]) + 1);
    }

    /* huffman table */
    put_marker(p, DHT);
    flush_put_bits(p);
    ptr = put_bits_ptr(p);
    put_bits(p, 16, 0); /* patched later */
    size = 2;

    // Only MJPEG can have a variable Huffman variable. All other
    // formats use the default Huffman table.
    if (s && s->huffman == HUFFMAN_TABLE_OPTIMAL) {
        size += put_huffman_table(p, 0, 0, s->mjpeg_ctx->bits_dc_luminance,
                                  s->mjpeg_ctx->val_dc_luminance);
        size += put_huffman_table(p, 0, 1, s->mjpeg_ctx->bits_dc_chrominance,
                                  s->mjpeg_ctx->val_dc_chrominance);

        size += put_huffman_table(p, 1, 0, s->mjpeg_ctx->bits_ac_luminance,
                                  s->mjpeg_ctx->val_ac_luminance);
        size += put_huffman_table(p, 1, 1, s->mjpeg_ctx->bits_ac_chrominance,
                                  s->mjpeg_ctx->val_ac_chrominance);
    } else {
        size += put_huffman_table(p, 0, 0, avpriv_mjpeg_bits_dc_luminance,
                                  avpriv_mjpeg_val_dc);
        size += put_huffman_table(p, 0, 1, avpriv_mjpeg_bits_dc_chrominance,
                                  avpriv_mjpeg_val_dc);

        size += put_huffman_table(p, 1, 0, avpriv_mjpeg_bits_ac_luminance,
                                  avpriv_mjpeg_val_ac_luminance);
        size += put_huffman_table(p, 1, 1, avpriv_mjpeg_bits_ac_chrominance,
                                  avpriv_mjpeg_val_ac_chrominance);
    }
    AV_WB16(ptr, size);
}