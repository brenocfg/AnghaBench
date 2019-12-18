#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  buffer; } ;
struct TYPE_10__ {int x; int y; } ;
struct TYPE_9__ {TYPE_5__ gbyte; TYPE_3__* mvectors; scalar_t__* size; int /*<<< orphan*/  mvectors_size; } ;
struct TYPE_8__ {int height; int width; TYPE_2__* priv_data; } ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_1__ AVCodecContext ;
typedef  TYPE_2__ AGMContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_fast_padded_malloc (TYPE_3__**,int /*<<< orphan*/ *,int) ; 
 scalar_t__ bytestream2_get_bytes_left (TYPE_5__*) ; 
 int /*<<< orphan*/  bytestream2_skip (TYPE_5__*,int) ; 
 int get_bits_count (int /*<<< orphan*/ *) ; 
 scalar_t__ get_bits_left (int /*<<< orphan*/ *) ; 
 int init_get_bits8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int read_code (int /*<<< orphan*/ *,int*,int*,int*,int) ; 

__attribute__((used)) static int decode_motion_vectors(AVCodecContext *avctx, GetBitContext *gb)
{
    AGMContext *s = avctx->priv_data;
    int nb_mvs = ((avctx->height + 15) >> 4) * ((avctx->width + 15) >> 4);
    int ret, skip = 0, value, map;

    av_fast_padded_malloc(&s->mvectors, &s->mvectors_size,
                          nb_mvs * sizeof(*s->mvectors));
    if (!s->mvectors)
        return AVERROR(ENOMEM);

    if ((ret = init_get_bits8(gb, s->gbyte.buffer, bytestream2_get_bytes_left(&s->gbyte) -
                                                   (s->size[0] + s->size[1] + s->size[2]))) < 0)
        return ret;

    memset(s->mvectors, 0, sizeof(*s->mvectors) * nb_mvs);

    for (int i = 0; i < nb_mvs; i++) {
        ret = read_code(gb, &skip, &value, &map, 1);
        if (ret < 0)
            return ret;
        s->mvectors[i].x = value;
        i += skip;
    }

    for (int i = 0; i < nb_mvs; i++) {
        ret = read_code(gb, &skip, &value, &map, 1);
        if (ret < 0)
            return ret;
        s->mvectors[i].y = value;
        i += skip;
    }

    if (get_bits_left(gb) <= 0)
        return AVERROR_INVALIDDATA;
    skip = (get_bits_count(gb) >> 3) + 1;
    bytestream2_skip(&s->gbyte, skip);

    return 0;
}