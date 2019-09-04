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
struct TYPE_3__ {unsigned char* buf; } ;
typedef  TYPE_1__ AVProbeData ;

/* Variables and functions */
 int AVPROBE_SCORE_MAX ; 
 scalar_t__ memcmp (unsigned char const*,char*,int) ; 

__attribute__((used)) static int vivo_probe(const AVProbeData *p)
{
    const unsigned char *buf = p->buf;
    unsigned c, length = 0;

    // stream must start with packet of type 0 and sequence number 0
    if (*buf++ != 0)
        return 0;

    // read at most 2 bytes of coded length
    c = *buf++;
    length = c & 0x7F;
    if (c & 0x80) {
        c = *buf++;
        length = (length << 7) | (c & 0x7F);
    }
    if (c & 0x80 || length > 1024 || length < 21)
        return 0;

    if (memcmp(buf, "\r\nVersion:Vivo/", 15))
        return 0;
    buf += 15;

    if (*buf < '0' || *buf > '2')
        return 0;

    return AVPROBE_SCORE_MAX;
}