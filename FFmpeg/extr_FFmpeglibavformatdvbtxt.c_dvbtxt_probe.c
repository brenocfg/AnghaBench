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
typedef  int uint8_t ;
struct TYPE_3__ {int* buf; int buf_size; } ;
typedef  TYPE_1__ AVProbeData ;

/* Variables and functions */
 int AVPROBE_SCORE_MAX ; 
 int /*<<< orphan*/  ff_data_identifier_is_teletext (int) ; 
 int /*<<< orphan*/  ff_data_unit_id_is_teletext (int const) ; 

__attribute__((used)) static int dvbtxt_probe(const AVProbeData *p)
{
    const uint8_t *end = p->buf + p->buf_size;
    const uint8_t *buf;

    /* The purpose of this is demuxer is to detect DVB teletext streams in
     * mpegts, so we reject invalid buffer sizes */
    if ((p->buf_size + 45) % 184 != 0)
        return 0;

    if (!ff_data_identifier_is_teletext(p->buf[0]))
        return 0;

    for (buf = p->buf + 1; buf < end; buf += 46) {
        if (!ff_data_unit_id_is_teletext(buf[0]) && buf[0] != 0xff)
            return 0;
        if (buf[1] != 0x2c)     // data_unit_length
            return 0;
    }

    return AVPROBE_SCORE_MAX / 2;
}