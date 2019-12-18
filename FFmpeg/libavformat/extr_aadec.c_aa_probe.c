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
 scalar_t__ AA_MAGIC ; 
 int AVPROBE_SCORE_MAX ; 
 scalar_t__ AV_RB32 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int aa_probe(const AVProbeData *p)
{
    uint8_t *buf = p->buf;

    // first 4 bytes are file size, next 4 bytes are the magic
    if (AV_RB32(buf+4) != AA_MAGIC)
        return 0;

    return AVPROBE_SCORE_MAX / 2;
}