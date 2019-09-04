#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_6__ {int num_y; int num_x; int /*<<< orphan*/  pb; TYPE_3__* avctx; scalar_t__ prefix_bytes; TYPE_2__* slice_args; } ;
typedef  TYPE_1__ VC2EncContext ;
struct TYPE_8__ {int /*<<< orphan*/  (* execute ) (TYPE_3__*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int,int) ;} ;
struct TYPE_7__ {scalar_t__ bytes; int /*<<< orphan*/  pb; } ;
typedef  TYPE_2__ SliceArgs ;

/* Variables and functions */
 int /*<<< orphan*/  avpriv_align_put_bits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  encode_hq_slice ; 
 int /*<<< orphan*/  flush_put_bits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_put_bits (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ * put_bits_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skip_put_bytes (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int encode_slices(VC2EncContext *s)
{
    uint8_t *buf;
    int slice_x, slice_y, skip = 0;
    SliceArgs *enc_args = s->slice_args;

    avpriv_align_put_bits(&s->pb);
    flush_put_bits(&s->pb);
    buf = put_bits_ptr(&s->pb);

    for (slice_y = 0; slice_y < s->num_y; slice_y++) {
        for (slice_x = 0; slice_x < s->num_x; slice_x++) {
            SliceArgs *args = &enc_args[s->num_x*slice_y + slice_x];
            init_put_bits(&args->pb, buf + skip, args->bytes+s->prefix_bytes);
            skip += args->bytes;
        }
    }

    s->avctx->execute(s->avctx, encode_hq_slice, enc_args, NULL, s->num_x*s->num_y,
                      sizeof(SliceArgs));

    skip_put_bytes(&s->pb, skip);

    return 0;
}