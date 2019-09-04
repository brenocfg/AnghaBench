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
struct TYPE_3__ {int buf_size; scalar_t__* buf; } ;
typedef  TYPE_1__ AVProbeData ;

/* Variables and functions */
 int AVPROBE_SCORE_MAX ; 

__attribute__((used)) static int seq_probe(const AVProbeData *p)
{
    int i;

    if (p->buf_size < 258)
        return 0;

    /* there's no real header in a .seq file, the only thing they have in common */
    /* is the first 256 bytes of the file which are always filled with 0 */
    for (i = 0; i < 256; i++)
        if (p->buf[i])
            return 0;

    if(p->buf[256]==0 && p->buf[257]==0)
        return 0;

    /* only one fourth of the score since the previous check is too naive */
    return AVPROBE_SCORE_MAX / 4;
}