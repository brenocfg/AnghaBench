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
struct TYPE_3__ {int* buf; } ;
typedef  TYPE_1__ AVProbeData ;

/* Variables and functions */
 int AVPROBE_SCORE_EXTENSION ; 
 int FLAC_CHMODE_MID_SIDE ; 
 int FLAC_MAX_CHANNELS ; 

__attribute__((used)) static int raw_flac_probe(const AVProbeData *p)
{
    if ((p->buf[2] & 0xF0) == 0)    // blocksize code invalid
        return 0;
    if ((p->buf[2] & 0x0F) == 0x0F) // sample rate code invalid
        return 0;
    if ((p->buf[3] & 0xF0) >= FLAC_MAX_CHANNELS + FLAC_CHMODE_MID_SIDE << 4)
        // channel mode invalid
        return 0;
    if ((p->buf[3] & 0x06) == 0x06) // bits per sample code invalid
        return 0;
    if ((p->buf[3] & 0x01) == 0x01) // reserved bit set
        return 0;
    return AVPROBE_SCORE_EXTENSION / 4 + 1;
}