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
struct TYPE_3__ {scalar_t__ buf_size; int* buf; } ;
typedef  TYPE_1__ AVProbeData ;

/* Variables and functions */
 scalar_t__ AUD_CHUNK_PREAMBLE_SIZE ; 
 scalar_t__ AUD_CHUNK_SIGNATURE ; 
 scalar_t__ AUD_HEADER_SIZE ; 
 int AVPROBE_SCORE_EXTENSION ; 
 int AV_RL16 (int*) ; 
 scalar_t__ AV_RL32 (int*) ; 

__attribute__((used)) static int wsaud_probe(const AVProbeData *p)
{
    int field;

    /* Probabilistic content detection strategy: There is no file signature
     * so perform sanity checks on various header parameters:
     *   8000 <= sample rate (16 bits) <= 48000  ==> 40001 acceptable numbers
     *   flags <= 0x03 (2 LSBs are used)         ==> 4 acceptable numbers
     *   compression type (8 bits) = 1 or 99     ==> 2 acceptable numbers
     *   first audio chunk signature (32 bits)   ==> 1 acceptable number
     * The number space contains 2^64 numbers. There are 40001 * 4 * 2 * 1 =
     * 320008 acceptable number combinations.
     */

    if (p->buf_size < AUD_HEADER_SIZE + AUD_CHUNK_PREAMBLE_SIZE)
        return 0;

    /* check sample rate */
    field = AV_RL16(&p->buf[0]);
    if ((field < 8000) || (field > 48000))
        return 0;

    /* enforce the rule that the top 6 bits of this flags field are reserved (0);
     * this might not be true, but enforce it until deemed unnecessary */
    if (p->buf[10] & 0xFC)
        return 0;

    if (p->buf[11] != 99 && p->buf[11] != 1)
        return 0;

    /* read ahead to the first audio chunk and validate the first header signature */
    if (AV_RL32(&p->buf[16]) != AUD_CHUNK_SIGNATURE)
        return 0;

    /* return 1/2 certainty since this file check is a little sketchy */
    return AVPROBE_SCORE_EXTENSION;
}