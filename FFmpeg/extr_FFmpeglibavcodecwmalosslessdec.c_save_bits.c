#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int frame_offset; int num_saved_bits; int max_frame_size; int packet_loss; int /*<<< orphan*/  gb; int /*<<< orphan*/  frame_data; int /*<<< orphan*/  pb; int /*<<< orphan*/  avctx; } ;
typedef  TYPE_1__ WmallDecodeCtx ;
struct TYPE_9__ {scalar_t__ buffer; } ;
typedef  int /*<<< orphan*/  PutBitContext ;
typedef  TYPE_2__ GetBitContext ;

/* Variables and functions */
 int FFMIN (int,int) ; 
 int /*<<< orphan*/  avpriv_copy_bits (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  avpriv_request_sample (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  flush_put_bits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_bits (TYPE_2__*,int) ; 
 int get_bits_count (TYPE_2__*) ; 
 int /*<<< orphan*/  init_get_bits (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  init_put_bits (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_bits (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skip_bits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skip_bits_long (TYPE_2__*,int) ; 

__attribute__((used)) static void save_bits(WmallDecodeCtx *s, GetBitContext* gb, int len,
                      int append)
{
    int buflen;
    PutBitContext tmp;

    /* when the frame data does not need to be concatenated, the input buffer
        is reset and additional bits from the previous frame are copied
        and skipped later so that a fast byte copy is possible */

    if (!append) {
        s->frame_offset   = get_bits_count(gb) & 7;
        s->num_saved_bits = s->frame_offset;
        init_put_bits(&s->pb, s->frame_data, s->max_frame_size);
    }

    buflen = (s->num_saved_bits + len + 8) >> 3;

    if (len <= 0 || buflen > s->max_frame_size) {
        avpriv_request_sample(s->avctx, "Too small input buffer");
        s->packet_loss = 1;
        s->num_saved_bits = 0;
        return;
    }

    s->num_saved_bits += len;
    if (!append) {
        avpriv_copy_bits(&s->pb, gb->buffer + (get_bits_count(gb) >> 3),
                         s->num_saved_bits);
    } else {
        int align = 8 - (get_bits_count(gb) & 7);
        align = FFMIN(align, len);
        put_bits(&s->pb, align, get_bits(gb, align));
        len -= align;
        avpriv_copy_bits(&s->pb, gb->buffer + (get_bits_count(gb) >> 3), len);
    }
    skip_bits_long(gb, len);

    tmp = s->pb;
    flush_put_bits(&tmp);

    init_get_bits(&s->gb, s->frame_data, s->num_saved_bits);
    skip_bits(&s->gb, s->frame_offset);
}