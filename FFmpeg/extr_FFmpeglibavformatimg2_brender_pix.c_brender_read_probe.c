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
typedef  int /*<<< orphan*/  brender_magic ;
struct TYPE_3__ {scalar_t__ buf; } ;
typedef  TYPE_1__ AVProbeData ;

/* Variables and functions */
 int AVPROBE_SCORE_MAX ; 
 int AV_RB32 (scalar_t__) ; 
 scalar_t__ memcmp (scalar_t__,int const*,int) ; 

__attribute__((used)) static int brender_read_probe(const AVProbeData *p)
{
    static const uint8_t brender_magic[16] = {
        0,0,0,0x12,0,0,0,8,0,0,0,2,0,0,0,2
    };

    if (memcmp(p->buf, brender_magic, sizeof(brender_magic)))
        return 0;

    if (AV_RB32(p->buf+16) != 0x03 &&
        AV_RB32(p->buf+16) != 0x3D)
        return 0;

    return AVPROBE_SCORE_MAX-10;
}