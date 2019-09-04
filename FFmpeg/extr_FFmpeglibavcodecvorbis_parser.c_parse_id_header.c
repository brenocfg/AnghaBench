#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_4__ {int* blocksize; } ;
typedef  TYPE_1__ AVVorbisParseContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_log (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ memcmp (int const*,char*,int) ; 

__attribute__((used)) static int parse_id_header(AVVorbisParseContext *s,
                           const uint8_t *buf, int buf_size)
{
    /* Id header should be 30 bytes */
    if (buf_size < 30) {
        av_log(s, AV_LOG_ERROR, "Id header is too short\n");
        return AVERROR_INVALIDDATA;
    }

    /* make sure this is the Id header */
    if (buf[0] != 1) {
        av_log(s, AV_LOG_ERROR, "Wrong packet type in Id header\n");
        return AVERROR_INVALIDDATA;
    }

    /* check for header signature */
    if (memcmp(&buf[1], "vorbis", 6)) {
        av_log(s, AV_LOG_ERROR, "Invalid packet signature in Id header\n");
        return AVERROR_INVALIDDATA;
    }

    if (!(buf[29] & 0x1)) {
        av_log(s, AV_LOG_ERROR, "Invalid framing bit in Id header\n");
        return AVERROR_INVALIDDATA;
    }

    s->blocksize[0] = 1 << (buf[28] & 0xF);
    s->blocksize[1] = 1 << (buf[28] >>  4);

    return 0;
}