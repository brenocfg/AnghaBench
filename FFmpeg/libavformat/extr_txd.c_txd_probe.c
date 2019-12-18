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
struct TYPE_3__ {scalar_t__ buf; } ;
typedef  TYPE_1__ AVProbeData ;

/* Variables and functions */
 int AVPROBE_SCORE_MAX ; 
 scalar_t__ AV_RL32 (scalar_t__) ; 
 scalar_t__ TXD_FILE ; 
 scalar_t__ TXD_MARKER ; 
 scalar_t__ TXD_MARKER2 ; 

__attribute__((used)) static int txd_probe(const AVProbeData * pd) {
    if (AV_RL32(pd->buf  ) == TXD_FILE &&
       (AV_RL32(pd->buf+8) == TXD_MARKER || AV_RL32(pd->buf+8) == TXD_MARKER2))
        return AVPROBE_SCORE_MAX;
    return 0;
}