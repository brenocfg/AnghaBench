#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ size; } ;
struct TYPE_5__ {int seen; int want; size_t pos; int /*<<< orphan*/ * bag; int /*<<< orphan*/  size; int /*<<< orphan*/  frames; } ;
typedef  TYPE_1__ MP3Context ;
typedef  TYPE_2__ AVPacket ;

/* Variables and functions */
 int XING_NUM_BAGS ; 

__attribute__((used)) static void mp3_xing_add_frame(MP3Context *mp3, AVPacket *pkt)
{
    int i;

    mp3->frames++;
    mp3->seen++;
    mp3->size += pkt->size;

    if (mp3->want == mp3->seen) {
        mp3->bag[mp3->pos] = mp3->size;

        if (XING_NUM_BAGS == ++mp3->pos) {
            /* shrink table to half size by throwing away each second bag. */
            for (i = 1; i < XING_NUM_BAGS; i += 2)
                mp3->bag[i >> 1] = mp3->bag[i];

            /* double wanted amount per bag. */
            mp3->want *= 2;
            /* adjust current position to half of table size. */
            mp3->pos = XING_NUM_BAGS / 2;
        }

        mp3->seen = 0;
    }
}