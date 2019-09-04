#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_9__ ;
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_12__ ;
typedef  struct TYPE_16__   TYPE_11__ ;
typedef  struct TYPE_15__   TYPE_10__ ;

/* Type definitions */
struct TYPE_21__ {int load_lum_quantiser_matrix; int load_chroma_quantiser_matrix; int* load_huffman_table; TYPE_3__* huffman_table; int /*<<< orphan*/ * chroma_quantiser_matrix; int /*<<< orphan*/ * lum_quantiser_matrix; } ;
typedef  TYPE_4__ VAQMatrixBufferJPEG ;
typedef  TYPE_4__ VAHuffmanTableBufferJPEGBaseline ;
typedef  int /*<<< orphan*/  VAAPIEncodePicture ;
struct TYPE_25__ {TYPE_10__* table; } ;
struct TYPE_23__ {int Ns; } ;
struct TYPE_19__ {TYPE_7__ header; } ;
struct TYPE_24__ {TYPE_1__* table; } ;
struct TYPE_16__ {size_t* Tq; int Nf; } ;
struct TYPE_22__ {TYPE_9__ huffman_tables; TYPE_2__ scan; TYPE_8__ quant_tables; TYPE_11__ frame_header; } ;
typedef  TYPE_6__ VAAPIEncodeMJPEGContext ;
struct TYPE_20__ {int* num_dc_codes; int* num_ac_codes; int /*<<< orphan*/ * ac_values; int /*<<< orphan*/ * dc_values; } ;
struct TYPE_18__ {int /*<<< orphan*/ * Q; } ;
struct TYPE_17__ {TYPE_6__* priv_data; } ;
struct TYPE_15__ {int* L; int /*<<< orphan*/ * V; } ;
typedef  TYPE_7__ JPEGRawScanHeader ;
typedef  TYPE_8__ JPEGRawQuantisationTableSpecification ;
typedef  TYPE_9__ JPEGRawHuffmanTableSpecification ;
typedef  TYPE_10__ JPEGRawHuffmanTable ;
typedef  TYPE_11__ JPEGRawFrameHeader ;
typedef  TYPE_12__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EOF ; 
 int /*<<< orphan*/  ENOSPC ; 
 int VAHuffmanTableBufferType ; 
 int VAQMatrixBufferType ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int vaapi_encode_mjpeg_write_extra_buffer(AVCodecContext *avctx,
                                                 VAAPIEncodePicture *pic,
                                                 int index, int *type,
                                                 char *data, size_t *data_len)
{
    VAAPIEncodeMJPEGContext *priv = avctx->priv_data;
    int t, i, k;

    if (index == 0) {
        // Write quantisation tables.
        JPEGRawFrameHeader                     *fh = &priv->frame_header;
        JPEGRawQuantisationTableSpecification *dqt = &priv->quant_tables;
        VAQMatrixBufferJPEG *quant;

        if (*data_len < sizeof(*quant))
            return AVERROR(ENOSPC);
        *type     = VAQMatrixBufferType;
        *data_len = sizeof(*quant);

        quant = (VAQMatrixBufferJPEG*)data;
        memset(quant, 0, sizeof(*quant));

        quant->load_lum_quantiser_matrix = 1;
        for (i = 0; i < 64; i++)
            quant->lum_quantiser_matrix[i] = dqt->table[fh->Tq[0]].Q[i];

        if (fh->Nf > 1) {
            quant->load_chroma_quantiser_matrix = 1;
            for (i = 0; i < 64; i++)
                quant->chroma_quantiser_matrix[i] =
                    dqt->table[fh->Tq[1]].Q[i];
        }

    } else if (index == 1) {
        // Write huffman tables.
        JPEGRawScanHeader                 *sh = &priv->scan.header;
        JPEGRawHuffmanTableSpecification *dht = &priv->huffman_tables;
        VAHuffmanTableBufferJPEGBaseline *huff;

        if (*data_len < sizeof(*huff))
            return AVERROR(ENOSPC);
        *type     = VAHuffmanTableBufferType;
        *data_len = sizeof(*huff);

        huff = (VAHuffmanTableBufferJPEGBaseline*)data;
        memset(huff, 0, sizeof(*huff));

        for (t = 0; t < 1 + (sh->Ns > 1); t++) {
            const JPEGRawHuffmanTable *ht;

            huff->load_huffman_table[t] = 1;

            ht = &dht->table[2 * t];
            for (i = k = 0; i < 16; i++)
                k += (huff->huffman_table[t].num_dc_codes[i] = ht->L[i]);
            av_assert0(k <= sizeof(huff->huffman_table[t].dc_values));
            for (i = 0; i < k; i++)
                huff->huffman_table[t].dc_values[i] = ht->V[i];

            ht = &dht->table[2 * t + 1];
            for (i = k = 0; i < 16; i++)
                k += (huff->huffman_table[t].num_ac_codes[i] = ht->L[i]);
            av_assert0(k <= sizeof(huff->huffman_table[t].ac_values));
            for (i = 0; i < k; i++)
                huff->huffman_table[t].ac_values[i] = ht->V[i];
        }

    } else {
        return AVERROR_EOF;
    }
    return 0;
}