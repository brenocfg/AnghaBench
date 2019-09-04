#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct TYPE_6__ {TYPE_1__* priv_data; } ;
struct TYPE_5__ {int max_payload_size; scalar_t__* buf; int /*<<< orphan*/  cur_timestamp; int /*<<< orphan*/  timestamp; } ;
typedef  TYPE_1__ RTPMuxContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int FFMIN (int,int) ; 
 scalar_t__* ff_h263_find_resync_marker_reverse (scalar_t__ const*,scalar_t__ const*) ; 
 int /*<<< orphan*/  ff_rtp_send_data (TYPE_2__*,scalar_t__*,int,int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__ const*,int) ; 

void ff_rtp_send_h263(AVFormatContext *s1, const uint8_t *buf1, int size)
{
    RTPMuxContext *s = s1->priv_data;
    int len, max_packet_size;
    uint8_t *q;

    max_packet_size = s->max_payload_size;

    while (size > 0) {
        q = s->buf;
        if (size >= 2 && (buf1[0] == 0) && (buf1[1] == 0)) {
            *q++ = 0x04;
            buf1 += 2;
            size -= 2;
        } else {
            *q++ = 0;
        }
        *q++ = 0;

        len = FFMIN(max_packet_size - 2, size);

        /* Look for a better place to split the frame into packets. */
        if (len < size) {
            const uint8_t *end = ff_h263_find_resync_marker_reverse(buf1,
                                                                    buf1 + len);
            len = end - buf1;
        }

        memcpy(q, buf1, len);
        q += len;

        /* 90 KHz time stamp */
        s->timestamp = s->cur_timestamp;
        ff_rtp_send_data(s1, s->buf, q - s->buf, (len == size));

        buf1 += len;
        size -= len;
    }
}