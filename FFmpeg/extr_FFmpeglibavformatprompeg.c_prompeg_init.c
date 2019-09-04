#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct TYPE_7__ {int flags; TYPE_2__* priv_data; } ;
typedef  TYPE_1__ URLContext ;
struct TYPE_9__ {void* bitstring; } ;
struct TYPE_8__ {int packet_idx_max; int l; int d; int packet_size; int length_recovery; int rtp_buf_size; int bitstring_size; int fec_arr_len; int rtp_col_sn; int rtp_row_sn; int first; scalar_t__ init; int /*<<< orphan*/ * rtp_buf; TYPE_4__** fec_arr; TYPE_4__** fec_col_tmp; TYPE_4__** fec_col; TYPE_4__* fec_row; scalar_t__ packet_idx; } ;
typedef  int /*<<< orphan*/  PrompegFec ;
typedef  TYPE_2__ PrompegContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int AVFMT_FLAG_BITEXACT ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  ENOMEM ; 
 int UINT16_MAX ; 
 int /*<<< orphan*/  av_freep (TYPE_4__**) ; 
 int av_get_random_seed () ; 
 int /*<<< orphan*/  av_log (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 TYPE_4__* av_malloc (int) ; 
 void* av_malloc_array (int,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int prompeg_init(URLContext *h, const uint8_t *buf, int size) {
    PrompegContext *s = h->priv_data;
    uint32_t seed;
    int i;

    s->fec_arr = NULL;
    s->rtp_buf = NULL;

    if (size < 12 || size > UINT16_MAX + 12) {
        av_log(h, AV_LOG_ERROR, "Invalid RTP packet size\n");
        return AVERROR_INVALIDDATA;
    }

    s->packet_idx = 0;
    s->packet_idx_max = s->l * s->d;
    s->packet_size = size;
    s->length_recovery = size - 12;
    s->rtp_buf_size = 28 + s->length_recovery; // 12 + 16: RTP + FEC headers
    s->bitstring_size = 8 + s->length_recovery; // 8: P, X, CC, M, PT, SN, TS
    s->fec_arr_len = 1 + 2 * s->l; // row + column tmp + column out

    if (h->flags & AVFMT_FLAG_BITEXACT) {
        s->rtp_col_sn = 0;
        s->rtp_row_sn = 0;
    } else {
        seed = av_get_random_seed();
        s->rtp_col_sn = seed & 0x0fff;
        s->rtp_row_sn = (seed >> 16) & 0x0fff;
    }

    s->fec_arr = av_malloc_array(s->fec_arr_len, sizeof (PrompegFec*));
    if (!s->fec_arr) {
        goto fail;
    }
    for (i = 0; i < s->fec_arr_len; i++) {
        s->fec_arr[i] = av_malloc(sizeof (PrompegFec));
        if (!s->fec_arr[i]) {
            goto fail;
        }
        s->fec_arr[i]->bitstring = av_malloc_array(s->bitstring_size, sizeof (uint8_t));
        if (!s->fec_arr[i]->bitstring) {
            av_freep(&s->fec_arr[i]);
            goto fail;
        }
    }
    s->fec_row = *s->fec_arr;
    s->fec_col = s->fec_arr + 1;
    s->fec_col_tmp = s->fec_arr + 1 + s->l;

    s->rtp_buf = av_malloc_array(s->rtp_buf_size, sizeof (uint8_t));
    if (!s->rtp_buf) {
        goto fail;
    }
    memset(s->rtp_buf, 0, s->rtp_buf_size);

    s->init = 0;
    s->first = 1;

    return 0;

fail:
    av_log(h, AV_LOG_ERROR, "Failed to allocate the FEC buffer\n");
    return AVERROR(ENOMEM);
}