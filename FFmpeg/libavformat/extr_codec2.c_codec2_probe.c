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
struct TYPE_3__ {scalar_t__* buf; } ;
typedef  TYPE_1__ AVProbeData ;

/* Variables and functions */
 scalar_t__ AVPRIV_CODEC2_MAGIC ; 
 int AVPROBE_SCORE_EXTENSION ; 
 scalar_t__ AV_RB24 (scalar_t__*) ; 
 scalar_t__ EXPECTED_CODEC2_MAJOR_VERSION ; 
 scalar_t__ EXPECTED_CODEC2_MINOR_VERSION ; 

__attribute__((used)) static int codec2_probe(const AVProbeData *p)
{
    //must start wih C0 DE C2
    if (AV_RB24(p->buf) != AVPRIV_CODEC2_MAGIC) {
        return 0;
    }

    //no .c2 files prior to 0.8
    //be strict about major version while we're at it
    if (p->buf[3] != EXPECTED_CODEC2_MAJOR_VERSION ||
        p->buf[4] <  EXPECTED_CODEC2_MINOR_VERSION) {
        return 0;
    }

    //32 bits of identification -> low score
    return AVPROBE_SCORE_EXTENSION + 1;
}