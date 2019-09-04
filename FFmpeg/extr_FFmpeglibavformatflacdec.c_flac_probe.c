#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int* buf; int buf_size; } ;
typedef  TYPE_1__ AVProbeData ;

/* Variables and functions */
 int AVPROBE_SCORE_EXTENSION ; 
 int AVPROBE_SCORE_MAX ; 
 int AV_RB16 (int*) ; 
 int AV_RB24 (int*) ; 
 int FLAC_METADATA_TYPE_STREAMINFO ; 
 int FLAC_STREAMINFO_SIZE ; 
 scalar_t__ memcmp (int*,char*,int) ; 
 int raw_flac_probe (TYPE_1__ const*) ; 

__attribute__((used)) static int flac_probe(const AVProbeData *p)
{
    if ((AV_RB16(p->buf) & 0xFFFE) == 0xFFF8)
        return raw_flac_probe(p);

    /* file header + metadata header + checked bytes of streaminfo */
    if (p->buf_size >= 4 + 4 + 13) {
        int type           = p->buf[4] & 0x7f;
        int size           = AV_RB24(p->buf + 5);
        int min_block_size = AV_RB16(p->buf + 8);
        int max_block_size = AV_RB16(p->buf + 10);
        int sample_rate    = AV_RB24(p->buf + 18) >> 4;

        if (memcmp(p->buf, "fLaC", 4))
            return 0;
        if (type == FLAC_METADATA_TYPE_STREAMINFO &&
            size == FLAC_STREAMINFO_SIZE          &&
            min_block_size >= 16                  &&
            max_block_size >= min_block_size      &&
            sample_rate && sample_rate <= 655350)
            return AVPROBE_SCORE_MAX;
        return AVPROBE_SCORE_EXTENSION;
    }

    return 0;
}