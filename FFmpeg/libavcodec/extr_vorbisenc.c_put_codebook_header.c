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
struct TYPE_3__ {int ndimensions; int nentries; int* lens; int lookup; int* quantlist; int seq_p; int /*<<< orphan*/  delta; int /*<<< orphan*/  min; } ;
typedef  TYPE_1__ vorbis_enc_codebook ;
typedef  int /*<<< orphan*/  PutBitContext ;

/* Variables and functions */
 int FFMAX (int,int) ; 
 int cb_lookup_vals (int,int,int) ; 
 int ilog (int) ; 
 int /*<<< orphan*/  put_bits (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  put_float (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void put_codebook_header(PutBitContext *pb, vorbis_enc_codebook *cb)
{
    int i;
    int ordered = 0;

    put_bits(pb, 24, 0x564342); //magic
    put_bits(pb, 16, cb->ndimensions);
    put_bits(pb, 24, cb->nentries);

    for (i = 1; i < cb->nentries; i++)
        if (cb->lens[i] < cb->lens[i-1])
            break;
    if (i == cb->nentries)
        ordered = 1;

    put_bits(pb, 1, ordered);
    if (ordered) {
        int len = cb->lens[0];
        put_bits(pb, 5, len - 1);
        i = 0;
        while (i < cb->nentries) {
            int j;
            for (j = 0; j+i < cb->nentries; j++)
                if (cb->lens[j+i] != len)
                    break;
            put_bits(pb, ilog(cb->nentries - i), j);
            i += j;
            len++;
        }
    } else {
        int sparse = 0;
        for (i = 0; i < cb->nentries; i++)
            if (!cb->lens[i])
                break;
        if (i != cb->nentries)
            sparse = 1;
        put_bits(pb, 1, sparse);

        for (i = 0; i < cb->nentries; i++) {
            if (sparse)
                put_bits(pb, 1, !!cb->lens[i]);
            if (cb->lens[i])
                put_bits(pb, 5, cb->lens[i] - 1);
        }
    }

    put_bits(pb, 4, cb->lookup);
    if (cb->lookup) {
        int tmp  = cb_lookup_vals(cb->lookup, cb->ndimensions, cb->nentries);
        int bits = ilog(cb->quantlist[0]);

        for (i = 1; i < tmp; i++)
            bits = FFMAX(bits, ilog(cb->quantlist[i]));

        put_float(pb, cb->min);
        put_float(pb, cb->delta);

        put_bits(pb, 4, bits - 1);
        put_bits(pb, 1, cb->seq_p);

        for (i = 0; i < tmp; i++)
            put_bits(pb, bits, cb->quantlist[i]);
    }
}