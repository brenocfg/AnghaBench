#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int huff_ncode; int /*<<< orphan*/  val_ac_chrominance; int /*<<< orphan*/  bits_ac_chrominance; int /*<<< orphan*/  huff_code_ac_chrominance; int /*<<< orphan*/  huff_size_ac_chrominance; int /*<<< orphan*/  val_ac_luminance; int /*<<< orphan*/  bits_ac_luminance; int /*<<< orphan*/  huff_code_ac_luminance; int /*<<< orphan*/  huff_size_ac_luminance; int /*<<< orphan*/  val_dc_chrominance; int /*<<< orphan*/  bits_dc_chrominance; int /*<<< orphan*/  huff_code_dc_chrominance; int /*<<< orphan*/  huff_size_dc_chrominance; int /*<<< orphan*/  val_dc_luminance; int /*<<< orphan*/  bits_dc_luminance; int /*<<< orphan*/  huff_code_dc_luminance; int /*<<< orphan*/  huff_size_dc_luminance; TYPE_1__* huff_buffer; } ;
struct TYPE_4__ {int table_id; int code; } ;
typedef  int /*<<< orphan*/  MJpegEncHuffmanContext ;
typedef  TYPE_2__ MJpegContext ;

/* Variables and functions */
 int /*<<< orphan*/  ff_mjpeg_build_huffman_codes (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_mjpeg_encode_huffman_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ff_mjpeg_encode_huffman_increment (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ff_mjpeg_encode_huffman_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ff_mjpeg_build_optimal_huffman(MJpegContext *m)
{
    int i, table_id, code;

    MJpegEncHuffmanContext dc_luminance_ctx;
    MJpegEncHuffmanContext dc_chrominance_ctx;
    MJpegEncHuffmanContext ac_luminance_ctx;
    MJpegEncHuffmanContext ac_chrominance_ctx;
    MJpegEncHuffmanContext *ctx[4] = {&dc_luminance_ctx,
                                      &dc_chrominance_ctx,
                                      &ac_luminance_ctx,
                                      &ac_chrominance_ctx};
    for (i = 0; i < 4; i++) {
        ff_mjpeg_encode_huffman_init(ctx[i]);
    }
    for (i = 0; i < m->huff_ncode; i++) {
        table_id = m->huff_buffer[i].table_id;
        code = m->huff_buffer[i].code;

        ff_mjpeg_encode_huffman_increment(ctx[table_id], code);
    }

    ff_mjpeg_encode_huffman_close(&dc_luminance_ctx,
                                  m->bits_dc_luminance,
                                  m->val_dc_luminance, 12);
    ff_mjpeg_encode_huffman_close(&dc_chrominance_ctx,
                                  m->bits_dc_chrominance,
                                  m->val_dc_chrominance, 12);
    ff_mjpeg_encode_huffman_close(&ac_luminance_ctx,
                                  m->bits_ac_luminance,
                                  m->val_ac_luminance, 256);
    ff_mjpeg_encode_huffman_close(&ac_chrominance_ctx,
                                  m->bits_ac_chrominance,
                                  m->val_ac_chrominance, 256);

    ff_mjpeg_build_huffman_codes(m->huff_size_dc_luminance,
                                 m->huff_code_dc_luminance,
                                 m->bits_dc_luminance,
                                 m->val_dc_luminance);
    ff_mjpeg_build_huffman_codes(m->huff_size_dc_chrominance,
                                 m->huff_code_dc_chrominance,
                                 m->bits_dc_chrominance,
                                 m->val_dc_chrominance);
    ff_mjpeg_build_huffman_codes(m->huff_size_ac_luminance,
                                 m->huff_code_ac_luminance,
                                 m->bits_ac_luminance,
                                 m->val_ac_luminance);
    ff_mjpeg_build_huffman_codes(m->huff_size_ac_chrominance,
                                 m->huff_code_ac_chrominance,
                                 m->bits_ac_chrominance,
                                 m->val_ac_chrominance);
}