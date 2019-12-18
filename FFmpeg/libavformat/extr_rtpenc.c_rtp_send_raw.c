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
struct TYPE_5__ {int max_payload_size; int /*<<< orphan*/  cur_timestamp; int /*<<< orphan*/  timestamp; } ;
typedef  TYPE_1__ RTPMuxContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  ff_rtp_send_data (TYPE_2__*,int /*<<< orphan*/  const*,int,int) ; 

__attribute__((used)) static void rtp_send_raw(AVFormatContext *s1,
                         const uint8_t *buf1, int size)
{
    RTPMuxContext *s = s1->priv_data;
    int len, max_packet_size;

    max_packet_size = s->max_payload_size;

    while (size > 0) {
        len = max_packet_size;
        if (len > size)
            len = size;

        s->timestamp = s->cur_timestamp;
        ff_rtp_send_data(s1, buf1, len, (len == size));

        buf1 += len;
        size -= len;
    }
}