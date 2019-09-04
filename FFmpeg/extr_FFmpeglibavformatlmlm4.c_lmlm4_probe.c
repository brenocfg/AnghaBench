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
struct TYPE_3__ {unsigned char* buf; } ;
typedef  TYPE_1__ AVProbeData ;

/* Variables and functions */
 int AVPROBE_SCORE_MAX ; 
 int AV_RB16 (unsigned char const*) ; 
 int AV_RB24 (unsigned char const*) ; 
 unsigned int AV_RB32 (unsigned char const*) ; 
 unsigned int LMLM4_INVALID ; 
 unsigned int LMLM4_MAX_PACKET_SIZE ; 
 unsigned int LMLM4_MPEG1L2 ; 

__attribute__((used)) static int lmlm4_probe(const AVProbeData *pd)
{
    const unsigned char *buf = pd->buf;
    unsigned int frame_type, packet_size;

    frame_type  = AV_RB16(buf + 2);
    packet_size = AV_RB32(buf + 4);

    if (!AV_RB16(buf) && frame_type <= LMLM4_MPEG1L2 && packet_size &&
        frame_type != LMLM4_INVALID && packet_size <= LMLM4_MAX_PACKET_SIZE) {
        if (frame_type == LMLM4_MPEG1L2) {
            if ((AV_RB16(buf + 8) & 0xfffe) != 0xfffc)
                return 0;
            /* I could calculate the audio framesize and compare with
             * packet_size-8, but that seems overkill */
            return AVPROBE_SCORE_MAX / 3;
        } else if (AV_RB24(buf + 8) == 0x000001) {    /* PES Signal */
            return AVPROBE_SCORE_MAX / 5;
        }
    }

    return 0;
}