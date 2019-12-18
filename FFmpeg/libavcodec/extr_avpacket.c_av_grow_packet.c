#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_6__ {int size; int /*<<< orphan*/ * data; } ;
struct TYPE_5__ {unsigned int size; int /*<<< orphan*/ * data; TYPE_3__* buf; } ;
typedef  TYPE_1__ AVPacket ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 unsigned int AV_INPUT_BUFFER_PADDING_SIZE ; 
 int /*<<< orphan*/  ENOMEM ; 
 unsigned int INT_MAX ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 TYPE_3__* av_buffer_alloc (int) ; 
 int av_buffer_realloc (TYPE_3__**,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 

int av_grow_packet(AVPacket *pkt, int grow_by)
{
    int new_size;
    av_assert0((unsigned)pkt->size <= INT_MAX - AV_INPUT_BUFFER_PADDING_SIZE);
    if ((unsigned)grow_by >
        INT_MAX - (pkt->size + AV_INPUT_BUFFER_PADDING_SIZE))
        return AVERROR(ENOMEM);

    new_size = pkt->size + grow_by + AV_INPUT_BUFFER_PADDING_SIZE;
    if (pkt->buf) {
        size_t data_offset;
        uint8_t *old_data = pkt->data;
        if (pkt->data == NULL) {
            data_offset = 0;
            pkt->data = pkt->buf->data;
        } else {
            data_offset = pkt->data - pkt->buf->data;
            if (data_offset > INT_MAX - new_size)
                return AVERROR(ENOMEM);
        }

        if (new_size + data_offset > pkt->buf->size) {
            int ret = av_buffer_realloc(&pkt->buf, new_size + data_offset);
            if (ret < 0) {
                pkt->data = old_data;
                return ret;
            }
            pkt->data = pkt->buf->data + data_offset;
        }
    } else {
        pkt->buf = av_buffer_alloc(new_size);
        if (!pkt->buf)
            return AVERROR(ENOMEM);
        if (pkt->size > 0)
            memcpy(pkt->buf->data, pkt->data, pkt->size);
        pkt->data = pkt->buf->data;
    }
    pkt->size += grow_by;
    memset(pkt->data + pkt->size, 0, AV_INPUT_BUFFER_PADDING_SIZE);

    return 0;
}