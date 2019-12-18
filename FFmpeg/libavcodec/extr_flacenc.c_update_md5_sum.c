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
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int int32_t ;
struct TYPE_8__ {int blocksize; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* bswap16_buf ) (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ;} ;
struct TYPE_9__ {int channels; int /*<<< orphan*/  md5ctx; int /*<<< orphan*/ * md5_buffer; TYPE_3__ frame; TYPE_2__ bdsp; TYPE_1__* avctx; int /*<<< orphan*/  md5_buffer_size; } ;
struct TYPE_6__ {int bits_per_raw_sample; } ;
typedef  TYPE_4__ FlacEncodeContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_WL24 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ENOMEM ; 
 scalar_t__ HAVE_BIGENDIAN ; 
 int /*<<< orphan*/  av_fast_malloc (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  av_md5_update (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int update_md5_sum(FlacEncodeContext *s, const void *samples)
{
    const uint8_t *buf;
    int buf_size = s->frame.blocksize * s->channels *
                   ((s->avctx->bits_per_raw_sample + 7) / 8);

    if (s->avctx->bits_per_raw_sample > 16 || HAVE_BIGENDIAN) {
        av_fast_malloc(&s->md5_buffer, &s->md5_buffer_size, buf_size);
        if (!s->md5_buffer)
            return AVERROR(ENOMEM);
    }

    if (s->avctx->bits_per_raw_sample <= 16) {
        buf = (const uint8_t *)samples;
#if HAVE_BIGENDIAN
        s->bdsp.bswap16_buf((uint16_t *) s->md5_buffer,
                            (const uint16_t *) samples, buf_size / 2);
        buf = s->md5_buffer;
#endif
    } else {
        int i;
        const int32_t *samples0 = samples;
        uint8_t *tmp            = s->md5_buffer;

        for (i = 0; i < s->frame.blocksize * s->channels; i++) {
            int32_t v = samples0[i] >> 8;
            AV_WL24(tmp + 3*i, v);
        }
        buf = s->md5_buffer;
    }
    av_md5_update(s->md5ctx, buf, buf_size);

    return 0;
}