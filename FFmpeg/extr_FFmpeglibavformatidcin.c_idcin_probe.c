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
 unsigned int AV_RL32 (int /*<<< orphan*/ *) ; 
 int HUFFMAN_TABLE_SIZE ; 

__attribute__((used)) static int idcin_probe(const AVProbeData *p)
{
    unsigned int number, sample_rate;
    unsigned int w, h;
    int i;

    /*
     * This is what you could call a "probabilistic" file check: id CIN
     * files don't have a definite file signature. In lieu of such a marker,
     * perform sanity checks on the 5 32-bit header fields:
     *  width, height: greater than 0, less than or equal to 1024
     * audio sample rate: greater than or equal to 8000, less than or
     *  equal to 48000, or 0 for no audio
     * audio sample width (bytes/sample): 0 for no audio, or 1 or 2
     * audio channels: 0 for no audio, or 1 or 2
     */

    /* check we have enough data to do all checks, otherwise the
       0-padding may cause a wrong recognition */
    if (p->buf_size < 20 + HUFFMAN_TABLE_SIZE + 12)
        return 0;

    /* check the video width */
    w = AV_RL32(&p->buf[0]);
    if ((w == 0) || (w > 1024))
       return 0;

    /* check the video height */
    h = AV_RL32(&p->buf[4]);
    if ((h == 0) || (h > 1024))
       return 0;

    /* check the audio sample rate */
    sample_rate = AV_RL32(&p->buf[8]);
    if (sample_rate && (sample_rate < 8000 || sample_rate > 48000))
        return 0;

    /* check the audio bytes/sample */
    number = AV_RL32(&p->buf[12]);
    if (number > 2 || sample_rate && !number)
        return 0;

    /* check the audio channels */
    number = AV_RL32(&p->buf[16]);
    if (number > 2 || sample_rate && !number)
        return 0;

    i = 20 + HUFFMAN_TABLE_SIZE;
    if (AV_RL32(&p->buf[i]) == 1)
        i += 768;

    if (i+12 > p->buf_size || AV_RL32(&p->buf[i+8]) != w*h)
        return 1;

    /* return half certainty since this check is a bit sketchy */
    return AVPROBE_SCORE_EXTENSION;
}