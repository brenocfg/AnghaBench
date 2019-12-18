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
struct TYPE_3__ {int buf_size; scalar_t__ buf; } ;
typedef  TYPE_1__ AVProbeData ;

/* Variables and functions */
 int AVPROBE_SCORE_MAX ; 
 int AV_RB32 (scalar_t__) ; 
 int CHUNK_SIZE ; 
 int TIVO_PES_FILEID ; 

__attribute__((used)) static int ty_probe(const AVProbeData *p)
{
    int i;

    for (i = 0; i + 12 < p->buf_size; i += CHUNK_SIZE) {
        if (AV_RB32(p->buf + i) == TIVO_PES_FILEID &&
            AV_RB32(p->buf + i + 4) == 0x02 &&
            AV_RB32(p->buf + i + 8) == CHUNK_SIZE) {
            return AVPROBE_SCORE_MAX;
        }
    }

    return 0;
}