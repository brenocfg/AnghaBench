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
typedef  int uint8_t ;
struct TYPE_4__ {int skip_packets; } ;
typedef  TYPE_1__ XMAParserContext ;
struct TYPE_5__ {int duration; int key_frame; TYPE_1__* priv_data; } ;
typedef  TYPE_2__ AVCodecParserContext ;
typedef  int /*<<< orphan*/  AVCodecContext ;

/* Variables and functions */

__attribute__((used)) static int xma_parse(AVCodecParserContext *s1, AVCodecContext *avctx,
                     const uint8_t **poutbuf, int *poutbuf_size,
                     const uint8_t *buf, int buf_size)
{
    XMAParserContext *s = s1->priv_data;

    if (buf_size % 2048 == 0) {
        int duration = 0, packet, nb_packets = buf_size / 2048;

        for (packet = 0; packet < nb_packets; packet++) {
            if (s->skip_packets == 0) {
                duration += buf[packet * 2048] * 128;
                s->skip_packets = buf[packet * 2048 + 3] + 1;
            }
            s->skip_packets--;
        }

        s1->duration = duration;
        s1->key_frame = !!duration;
    }

    /* always return the full packet. this parser isn't doing any splitting or
       combining, only packet analysis */
    *poutbuf      = buf;
    *poutbuf_size = buf_size;
    return buf_size;
}