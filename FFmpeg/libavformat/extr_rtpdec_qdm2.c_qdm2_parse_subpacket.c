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
struct TYPE_3__ {int* len; int /*<<< orphan*/ ** buf; } ;
typedef  TYPE_1__ PayloadContext ;
typedef  int /*<<< orphan*/  AVStream ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 unsigned int AV_RB16 (int /*<<< orphan*/  const*) ; 
 unsigned int FFMIN (unsigned int,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned int) ; 

__attribute__((used)) static int qdm2_parse_subpacket(PayloadContext *qdm, AVStream *st,
                                const uint8_t *buf, const uint8_t *end)
{
    const uint8_t *p = buf;
    unsigned int id, len, type, to_copy;

    /* parse header so we know the size of the header/data */
    id       = *p++;
    type     = *p++;
    if (type & 0x80) {
        len   = AV_RB16(p);
        p    += 2;
        type &= 0x7F;
    } else
        len = *p++;

    if (end - p < len + (type == 0x7F) || id >= 0x80)
        return AVERROR_INVALIDDATA;
    if (type == 0x7F)
        type |= *p++ << 8;

    /* copy data into a temporary buffer */
    to_copy = FFMIN(len + (p - &buf[1]), 0x800 - qdm->len[id]);
    memcpy(&qdm->buf[id][qdm->len[id]], buf + 1, to_copy);
    qdm->len[id] += to_copy;

    return p + len - buf;
}