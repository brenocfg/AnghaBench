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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_6__ {TYPE_1__* priv_data; } ;
struct TYPE_5__ {int max_payload_size; int buf_ptr; int buf; int /*<<< orphan*/  cur_timestamp; int /*<<< orphan*/  timestamp; } ;
typedef  TYPE_1__ RTPMuxContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int TS_PACKET_SIZE ; 
 int /*<<< orphan*/  ff_rtp_send_data (TYPE_2__*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static void rtp_send_mpegts_raw(AVFormatContext *s1,
                                const uint8_t *buf1, int size)
{
    RTPMuxContext *s = s1->priv_data;
    int len, out_len;

    s->timestamp = s->cur_timestamp;
    while (size >= TS_PACKET_SIZE) {
        len = s->max_payload_size - (s->buf_ptr - s->buf);
        if (len > size)
            len = size;
        memcpy(s->buf_ptr, buf1, len);
        buf1 += len;
        size -= len;
        s->buf_ptr += len;

        out_len = s->buf_ptr - s->buf;
        if (out_len >= s->max_payload_size) {
            ff_rtp_send_data(s1, s->buf, out_len, 0);
            s->buf_ptr = s->buf;
        }
    }
}