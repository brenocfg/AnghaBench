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
struct TYPE_3__ {int buf_size; scalar_t__ buf; } ;
typedef  TYPE_1__ AVProbeData ;

/* Variables and functions */
 int AVPROBE_SCORE_MAX ; 
 int AV_RB16 (scalar_t__) ; 
 int AV_RB32 (scalar_t__) ; 
 scalar_t__ ff_dnxhd_parse_header_prefix (scalar_t__) ; 

__attribute__((used)) static int dnxhd_probe(const AVProbeData *p)
{
    int w, h, compression_id;
    if (p->buf_size < 0x2c)
        return 0;
    if (ff_dnxhd_parse_header_prefix(p->buf) == 0)
        return 0;
    h = AV_RB16(p->buf + 0x18);
    w = AV_RB16(p->buf + 0x1a);
    if (!w || !h)
        return 0;
    compression_id = AV_RB32(p->buf + 0x28);
    if ((compression_id < 1235 || compression_id > 1260) &&
        (compression_id < 1270 || compression_id > 1274))
        return 0;
    return AVPROBE_SCORE_MAX;
}