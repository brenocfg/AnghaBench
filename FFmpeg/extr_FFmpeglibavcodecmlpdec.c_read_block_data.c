#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ access_unit_size; int /*<<< orphan*/  avctx; int /*<<< orphan*/ ** bypassed_lsbs; TYPE_1__* substream; } ;
struct TYPE_6__ {scalar_t__ blockpos; scalar_t__ blocksize; unsigned int min_channel; unsigned int max_channel; scalar_t__ data_check_present; } ;
typedef  TYPE_1__ SubStream ;
typedef  TYPE_2__ MLPDecodeContext ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  avpriv_request_sample (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  filter_channel (TYPE_2__*,unsigned int,unsigned int) ; 
 scalar_t__ get_bits (int /*<<< orphan*/ *,int) ; 
 unsigned int get_bits_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int read_huff_channels (TYPE_2__*,int /*<<< orphan*/ *,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  skip_bits (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int read_block_data(MLPDecodeContext *m, GetBitContext *gbp,
                           unsigned int substr)
{
    SubStream *s = &m->substream[substr];
    unsigned int i, ch, expected_stream_pos = 0;
    int ret;

    if (s->data_check_present) {
        expected_stream_pos  = get_bits_count(gbp);
        expected_stream_pos += get_bits(gbp, 16);
        avpriv_request_sample(m->avctx,
                              "Substreams with VLC block size check info");
    }

    if (s->blockpos + s->blocksize > m->access_unit_size) {
        av_log(m->avctx, AV_LOG_ERROR, "too many audio samples in frame\n");
        return AVERROR_INVALIDDATA;
    }

    memset(&m->bypassed_lsbs[s->blockpos][0], 0,
           s->blocksize * sizeof(m->bypassed_lsbs[0]));

    for (i = 0; i < s->blocksize; i++)
        if ((ret = read_huff_channels(m, gbp, substr, i)) < 0)
            return ret;

    for (ch = s->min_channel; ch <= s->max_channel; ch++)
        filter_channel(m, substr, ch);

    s->blockpos += s->blocksize;

    if (s->data_check_present) {
        if (get_bits_count(gbp) != expected_stream_pos)
            av_log(m->avctx, AV_LOG_ERROR, "block data length mismatch\n");
        skip_bits(gbp, 8);
    }

    return 0;
}