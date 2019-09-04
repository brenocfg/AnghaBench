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
struct TYPE_3__ {int buf_size; int /*<<< orphan*/ * buf; } ;
typedef  TYPE_1__ AVProbeData ;

/* Variables and functions */
 int AVPROBE_SCORE_EXTENSION ; 
 int AV_RL16 (int /*<<< orphan*/ *) ; 
 int VMD_HEADER_SIZE ; 

__attribute__((used)) static int vmd_probe(const AVProbeData *p)
{
    int w, h, sample_rate;
    if (p->buf_size < 806)
        return 0;
    /* check if the first 2 bytes of the file contain the appropriate size
     * of a VMD header chunk */
    if (AV_RL16(&p->buf[0]) != VMD_HEADER_SIZE - 2)
        return 0;
    w = AV_RL16(&p->buf[12]);
    h = AV_RL16(&p->buf[14]);
    sample_rate = AV_RL16(&p->buf[804]);
    if ((!w || w > 2048 || !h || h > 2048) &&
        sample_rate != 22050)
        return 0;

    /* only return half certainty since this check is a bit sketchy */
    return AVPROBE_SCORE_EXTENSION;
}