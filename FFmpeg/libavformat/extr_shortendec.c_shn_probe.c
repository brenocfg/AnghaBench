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
struct TYPE_3__ {int* buf; int buf_size; } ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_1__ AVProbeData ;

/* Variables and functions */
 int AVPROBE_SCORE_EXTENSION ; 
 int AV_INPUT_BUFFER_PADDING_SIZE ; 
 int AV_RB32 (int*) ; 
 void* get_ur_golomb_shorten (int /*<<< orphan*/ *,unsigned int) ; 
 scalar_t__ init_get_bits8 (int /*<<< orphan*/ *,int*,int) ; 

__attribute__((used)) static int shn_probe(const AVProbeData *p)
{
    GetBitContext gb;
    int version, internal_ftype, channels, blocksize;

    if (AV_RB32(p->buf) != 0x616a6b67)
        return 0;
    version = p->buf[4];
    if (init_get_bits8(&gb, p->buf + 5, p->buf_size - 5 - AV_INPUT_BUFFER_PADDING_SIZE) < 0)
        return 0;
    if (!version) {
        internal_ftype = get_ur_golomb_shorten(&gb, 4);
        channels = get_ur_golomb_shorten(&gb, 0);
        blocksize = 256;
    } else {
        unsigned k;
        k = get_ur_golomb_shorten(&gb, 2);
        if (k > 31)
            return 0;
        internal_ftype = get_ur_golomb_shorten(&gb, k);
        k = get_ur_golomb_shorten(&gb, 2);
        if (k > 31)
            return 0;
        channels = get_ur_golomb_shorten(&gb, k);
        k = get_ur_golomb_shorten(&gb, 2);
        if (k > 31)
            return 0;
        blocksize = get_ur_golomb_shorten(&gb, k);
    }

    if (internal_ftype != 2 && internal_ftype != 3 && internal_ftype != 5)
        return 0;
    if (channels < 1 || channels > 8)
        return 0;
    if (blocksize < 1 || blocksize > 65535)
        return 0;

    return AVPROBE_SCORE_EXTENSION + 1;
}