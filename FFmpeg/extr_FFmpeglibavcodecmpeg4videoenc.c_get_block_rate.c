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
typedef  int int16_t ;
struct TYPE_3__ {scalar_t__ ac_esc_length; scalar_t__* intra_ac_vlc_last_length; scalar_t__* intra_ac_vlc_length; } ;
typedef  TYPE_1__ MpegEncContext ;

/* Variables and functions */
 size_t UNI_AC_ENC_INDEX (int,int) ; 

__attribute__((used)) static inline int get_block_rate(MpegEncContext *s, int16_t block[64],
                                 int block_last_index, uint8_t scantable[64])
{
    int last = 0;
    int j;
    int rate = 0;

    for (j = 1; j <= block_last_index; j++) {
        const int index = scantable[j];
        int level = block[index];
        if (level) {
            level += 64;
            if ((level & (~127)) == 0) {
                if (j < block_last_index)
                    rate += s->intra_ac_vlc_length[UNI_AC_ENC_INDEX(j - last - 1, level)];
                else
                    rate += s->intra_ac_vlc_last_length[UNI_AC_ENC_INDEX(j - last - 1, level)];
            } else
                rate += s->ac_esc_length;

            last = j;
        }
    }

    return rate;
}