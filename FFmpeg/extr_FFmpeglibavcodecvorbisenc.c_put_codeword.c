#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int nentries; int* lens; int /*<<< orphan*/ * codewords; } ;
typedef  TYPE_1__ vorbis_enc_codebook ;
struct TYPE_8__ {int size_in_bits; } ;
typedef  TYPE_2__ PutBitContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  av_assert2 (int) ; 
 int /*<<< orphan*/  put_bits (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int put_bits_count (TYPE_2__*) ; 

__attribute__((used)) static inline int put_codeword(PutBitContext *pb, vorbis_enc_codebook *cb,
                               int entry)
{
    av_assert2(entry >= 0);
    av_assert2(entry < cb->nentries);
    av_assert2(cb->lens[entry]);
    if (pb->size_in_bits - put_bits_count(pb) < cb->lens[entry])
        return AVERROR(EINVAL);
    put_bits(pb, cb->lens[entry], cb->codewords[entry]);
    return 0;
}