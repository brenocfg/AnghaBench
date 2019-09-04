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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_5__ {TYPE_1__* priv_data; } ;
struct TYPE_4__ {int packet_index; int packet_len; int /*<<< orphan*/ * packet; } ;
typedef  TYPE_1__ DVDSubParseContext ;
typedef  TYPE_2__ AVCodecParserContext ;
typedef  int /*<<< orphan*/  AVCodecContext ;

/* Variables and functions */
 unsigned int AV_INPUT_BUFFER_PADDING_SIZE ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int AV_RB16 (int /*<<< orphan*/  const*) ; 
 int AV_RB32 (int /*<<< orphan*/  const*) ; 
 unsigned int INT_MAX ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/ * av_malloc (unsigned int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int dvdsub_parse(AVCodecParserContext *s,
                        AVCodecContext *avctx,
                        const uint8_t **poutbuf, int *poutbuf_size,
                        const uint8_t *buf, int buf_size)
{
    DVDSubParseContext *pc = s->priv_data;

    *poutbuf      = buf;
    *poutbuf_size = buf_size;

    if (pc->packet_index == 0) {
        if (buf_size < 2 || AV_RB16(buf) && buf_size < 6) {
            if (buf_size)
                av_log(avctx, AV_LOG_DEBUG, "Parser input %d too small\n", buf_size);
            return buf_size;
        }
        pc->packet_len = AV_RB16(buf);
        if (pc->packet_len == 0) /* HD-DVD subpicture packet */
            pc->packet_len = AV_RB32(buf+2);
        av_freep(&pc->packet);
        if ((unsigned)pc->packet_len > INT_MAX - AV_INPUT_BUFFER_PADDING_SIZE) {
            av_log(avctx, AV_LOG_ERROR, "packet length %d is invalid\n", pc->packet_len);
            return buf_size;
        }
        pc->packet = av_malloc(pc->packet_len + AV_INPUT_BUFFER_PADDING_SIZE);
    }
    if (pc->packet) {
        if (pc->packet_index + buf_size <= pc->packet_len) {
            memcpy(pc->packet + pc->packet_index, buf, buf_size);
            pc->packet_index += buf_size;
            if (pc->packet_index >= pc->packet_len) {
                *poutbuf = pc->packet;
                *poutbuf_size = pc->packet_len;
                pc->packet_index = 0;
                return buf_size;
            }
        } else {
            /* erroneous size */
            pc->packet_index = 0;
        }
    }
    *poutbuf = NULL;
    *poutbuf_size = 0;
    return buf_size;
}