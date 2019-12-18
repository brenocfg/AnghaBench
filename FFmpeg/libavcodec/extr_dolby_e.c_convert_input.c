#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int input_size; int word_bits; int /*<<< orphan*/ * buffer; int /*<<< orphan*/  gb; int /*<<< orphan*/  avctx; int /*<<< orphan*/ * input; } ;
typedef  int /*<<< orphan*/  PutBitContext ;
typedef  TYPE_1__ DBEContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int AV_RB16 (int /*<<< orphan*/ *) ; 
 int AV_RB24 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AV_WB16 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  AV_WB24 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  flush_put_bits (int /*<<< orphan*/ *) ; 
 int init_get_bits (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  init_put_bits (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  put_bits (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int convert_input(DBEContext *s, int nb_words, int key)
{
    uint8_t *src = s->input;
    uint8_t *dst = s->buffer;
    PutBitContext pb;
    int i;

    av_assert0(nb_words <= 1024u);

    if (nb_words > s->input_size) {
        av_log(s->avctx, AV_LOG_ERROR, "Packet too short\n");
        return AVERROR_INVALIDDATA;
    }

    switch (s->word_bits) {
    case 16:
        for (i = 0; i < nb_words; i++, src += 2, dst += 2)
            AV_WB16(dst, AV_RB16(src) ^ key);
        break;
    case 20:
        init_put_bits(&pb, s->buffer, sizeof(s->buffer));
        for (i = 0; i < nb_words; i++, src += 3)
            put_bits(&pb, 20, AV_RB24(src) >> 4 ^ key);
        flush_put_bits(&pb);
        break;
    case 24:
        for (i = 0; i < nb_words; i++, src += 3, dst += 3)
            AV_WB24(dst, AV_RB24(src) ^ key);
        break;
    default:
        av_assert0(0);
    }

    return init_get_bits(&s->gb, s->buffer, nb_words * s->word_bits);
}