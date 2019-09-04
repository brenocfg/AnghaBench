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
struct TYPE_3__ {int /*<<< orphan*/ * buf; } ;
typedef  TYPE_1__ AVProbeData ;

/* Variables and functions */
 int AVPROBE_SCORE_MAX ; 
 int AV_RB64 (int /*<<< orphan*/  const*) ; 
 scalar_t__ AV_RL32 (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int dds_probe(const AVProbeData *p)
{
    const uint8_t *b = p->buf;

    if (   AV_RB64(b) == 0x444453207c000000
        && AV_RL32(b +  8)
        && AV_RL32(b + 12))
        return AVPROBE_SCORE_MAX - 1;
    return 0;
}