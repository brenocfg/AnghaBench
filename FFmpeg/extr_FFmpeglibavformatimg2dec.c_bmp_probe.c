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
 int AVPROBE_SCORE_EXTENSION ; 
 int AV_RB16 (int /*<<< orphan*/  const*) ; 
 int AV_RL32 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  AV_RN32 (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int bmp_probe(const AVProbeData *p)
{
    const uint8_t *b = p->buf;
    int ihsize;

    if (AV_RB16(b) != 0x424d)
        return 0;

    ihsize = AV_RL32(b+14);
    if (ihsize < 12 || ihsize > 255)
        return 0;

    if (!AV_RN32(b + 6)) {
        return AVPROBE_SCORE_EXTENSION + 1;
    }
    return AVPROBE_SCORE_EXTENSION / 4;
}