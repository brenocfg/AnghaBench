#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_5__ {int max_blocksize; int min_framesize; int max_framesize; int samplerate; int channels; int sample_count; int /*<<< orphan*/  md5sum; TYPE_1__* avctx; } ;
struct TYPE_4__ {int bits_per_raw_sample; } ;
typedef  int /*<<< orphan*/  PutBitContext ;
typedef  TYPE_2__ FlacEncodeContext ;

/* Variables and functions */
 int /*<<< orphan*/  FLAC_STREAMINFO_SIZE ; 
 int /*<<< orphan*/  flush_put_bits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_put_bits (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_bits (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void write_streaminfo(FlacEncodeContext *s, uint8_t *header)
{
    PutBitContext pb;

    memset(header, 0, FLAC_STREAMINFO_SIZE);
    init_put_bits(&pb, header, FLAC_STREAMINFO_SIZE);

    /* streaminfo metadata block */
    put_bits(&pb, 16, s->max_blocksize);
    put_bits(&pb, 16, s->max_blocksize);
    put_bits(&pb, 24, s->min_framesize);
    put_bits(&pb, 24, s->max_framesize);
    put_bits(&pb, 20, s->samplerate);
    put_bits(&pb, 3, s->channels-1);
    put_bits(&pb,  5, s->avctx->bits_per_raw_sample - 1);
    /* write 36-bit sample count in 2 put_bits() calls */
    put_bits(&pb, 24, (s->sample_count & 0xFFFFFF000LL) >> 12);
    put_bits(&pb, 12,  s->sample_count & 0x000000FFFLL);
    flush_put_bits(&pb);
    memcpy(&header[18], s->md5sum, 16);
}