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
struct TYPE_3__ {int buf_size; int /*<<< orphan*/ * buf; } ;
typedef  TYPE_1__ AVProbeData ;

/* Variables and functions */
 int AVPROBE_SCORE_EXTENSION ; 
 int AVPROBE_SCORE_MAX ; 
 scalar_t__ AV_RB16 (int /*<<< orphan*/  const*) ; 
 int AV_RB64 (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int qdraw_probe(const AVProbeData *p)
{
    const uint8_t *b = p->buf;

    if (   p->buf_size >= 528
        && (AV_RB64(b + 520) & 0xFFFFFFFFFFFF) == 0x001102ff0c00
        && AV_RB16(b + 520)
        && AV_RB16(b + 518))
        return AVPROBE_SCORE_MAX * 3 / 4;
    if (   (AV_RB64(b + 8) & 0xFFFFFFFFFFFF) == 0x001102ff0c00
        && AV_RB16(b + 8)
        && AV_RB16(b + 6))
        return AVPROBE_SCORE_EXTENSION / 4;
    return 0;
}