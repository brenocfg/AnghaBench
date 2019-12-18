#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {float* dimensions; int nentries; int ndimensions; float* pow2; int /*<<< orphan*/ * lens; } ;
typedef  TYPE_1__ vorbis_enc_codebook ;
typedef  int /*<<< orphan*/  PutBitContext ;

/* Variables and functions */
 float FLT_MAX ; 
 int /*<<< orphan*/  assert (float*) ; 
 scalar_t__ put_codeword (int /*<<< orphan*/ *,TYPE_1__*,int) ; 

__attribute__((used)) static float *put_vector(vorbis_enc_codebook *book, PutBitContext *pb,
                         float *num)
{
    int i, entry = -1;
    float distance = FLT_MAX;
    assert(book->dimensions);
    for (i = 0; i < book->nentries; i++) {
        float * vec = book->dimensions + i * book->ndimensions, d = book->pow2[i];
        int j;
        if (!book->lens[i])
            continue;
        for (j = 0; j < book->ndimensions; j++)
            d -= vec[j] * num[j];
        if (distance > d) {
            entry    = i;
            distance = d;
        }
    }
    if (put_codeword(pb, book, entry))
        return NULL;
    return &book->dimensions[entry * book->ndimensions];
}