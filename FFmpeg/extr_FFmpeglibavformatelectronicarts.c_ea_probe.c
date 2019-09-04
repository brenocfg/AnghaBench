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
struct TYPE_3__ {int /*<<< orphan*/ * buf; } ;
typedef  TYPE_1__ AVProbeData ;

/* Variables and functions */
#define  AVP6_TAG 137 
 int AVPROBE_SCORE_MAX ; 
 int AV_RL32 (int /*<<< orphan*/ *) ; 
#define  ISNh_TAG 136 
#define  MADk_TAG 135 
#define  MPCh_TAG 134 
#define  MVIh_TAG 133 
#define  MVhd_TAG 132 
#define  SCHl_TAG 131 
#define  SEAD_TAG 130 
#define  SHEN_TAG 129 
 unsigned int av_bswap32 (unsigned int) ; 
#define  kVGT_TAG 128 

__attribute__((used)) static int ea_probe(const AVProbeData *p)
{
    unsigned big_endian, size;

    switch (AV_RL32(&p->buf[0])) {
    case ISNh_TAG:
    case SCHl_TAG:
    case SEAD_TAG:
    case SHEN_TAG:
    case kVGT_TAG:
    case MADk_TAG:
    case MPCh_TAG:
    case MVhd_TAG:
    case MVIh_TAG:
    case AVP6_TAG:
        break;
    default:
        return 0;
    }
    size = AV_RL32(&p->buf[4]);
    big_endian = size > 0x000FFFFF;
    if (big_endian)
        size = av_bswap32(size);
    if (size > 0xfffff || size < 8)
        return 0;

    return AVPROBE_SCORE_MAX;
}