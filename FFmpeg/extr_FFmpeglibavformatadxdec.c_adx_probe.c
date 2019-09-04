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
struct TYPE_3__ {int buf_size; int /*<<< orphan*/ * buf; } ;
typedef  TYPE_1__ AVProbeData ;

/* Variables and functions */
 int AVPROBE_SCORE_MAX ; 
 int AV_RB16 (int /*<<< orphan*/ *) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static int adx_probe(const AVProbeData *p)
{
    int offset;
    if (AV_RB16(p->buf) != 0x8000)
        return 0;
    offset = AV_RB16(&p->buf[2]);
    if (   offset < 8
        || offset > p->buf_size - 4
        || memcmp(p->buf + offset - 2, "(c)CRI", 6))
        return 0;
    return AVPROBE_SCORE_MAX * 3 / 4;
}