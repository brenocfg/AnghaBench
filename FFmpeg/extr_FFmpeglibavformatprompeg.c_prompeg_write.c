#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_9__ {TYPE_3__* priv_data; } ;
typedef  TYPE_1__ URLContext ;
struct TYPE_11__ {int packet_idx; int l; int d; int packet_idx_max; scalar_t__ first; TYPE_2__** fec_col; int /*<<< orphan*/  bitstring_size; TYPE_2__** fec_col_tmp; TYPE_2__* fec_row; scalar_t__ init; } ;
struct TYPE_10__ {int /*<<< orphan*/  bitstring; void* ts; void* sn; } ;
typedef  TYPE_2__ PrompegFec ;
typedef  TYPE_3__ PrompegContext ;

/* Variables and functions */
 void* AV_RB16 (int /*<<< orphan*/  const*) ; 
 void* AV_RB32 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  PROMPEG_FEC_COL ; 
 int /*<<< orphan*/  PROMPEG_FEC_ROW ; 
 int /*<<< orphan*/  av_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int prompeg_create_bitstring (TYPE_1__*,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ **) ; 
 int prompeg_init (TYPE_1__*,int /*<<< orphan*/  const*,int) ; 
 int prompeg_write_fec (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xor_fast (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int prompeg_write(URLContext *h, const uint8_t *buf, int size) {
    PrompegContext *s = h->priv_data;
    PrompegFec *fec_tmp;
    uint8_t *bitstring = NULL;
    int col_idx, col_out_idx, row_idx;
    int ret, written = 0;

    if (s->init && ((ret = prompeg_init(h, buf, size)) < 0))
        goto end;

    if ((ret = prompeg_create_bitstring(h, buf, size, &bitstring)) < 0)
        goto end;

    col_idx = s->packet_idx % s->l;
    row_idx = s->packet_idx / s->l % s->d;

    // FEC' (row) send block-aligned, xor
    if (col_idx == 0) {
        if (!s->first || s->packet_idx > 0) {
            if ((ret = prompeg_write_fec(h, s->fec_row, PROMPEG_FEC_ROW)) < 0)
                goto end;
            written += ret;
        }
        memcpy(s->fec_row->bitstring, bitstring, s->bitstring_size);
        s->fec_row->sn = AV_RB16(buf + 2);
        s->fec_row->ts = AV_RB32(buf + 4);
    } else {
        xor_fast(s->fec_row->bitstring, bitstring, s->fec_row->bitstring,
                s->bitstring_size);
    }

    // FEC (column) xor
    if (row_idx == 0) {
        if (!s->first) {
            // swap fec_col and fec_col_tmp
            fec_tmp = s->fec_col[col_idx];
            s->fec_col[col_idx] = s->fec_col_tmp[col_idx];
            s->fec_col_tmp[col_idx] = fec_tmp;
        }
        memcpy(s->fec_col_tmp[col_idx]->bitstring, bitstring, s->bitstring_size);
        s->fec_col_tmp[col_idx]->sn = AV_RB16(buf + 2);
        s->fec_col_tmp[col_idx]->ts = AV_RB32(buf + 4);
    } else {
        xor_fast(s->fec_col_tmp[col_idx]->bitstring, bitstring,
                s->fec_col_tmp[col_idx]->bitstring, s->bitstring_size);
    }

    // FEC (column) send block-aligned
    if (!s->first && s->packet_idx % s->d == 0) {
        col_out_idx = s->packet_idx / s->d;
        if ((ret = prompeg_write_fec(h, s->fec_col[col_out_idx], PROMPEG_FEC_COL)) < 0)
            goto end;
        written += ret;
    }

    if (++s->packet_idx >= s->packet_idx_max) {
        s->packet_idx = 0;
        if (s->first)
            s->first = 0;
    }

    ret = written;

end:
    av_free(bitstring);
    return ret;
}