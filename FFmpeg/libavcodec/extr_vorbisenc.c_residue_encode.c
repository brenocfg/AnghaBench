#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int partition_size; int end; int begin; int type; size_t classbook; int classifications; float** maxes; int** books; } ;
typedef  TYPE_1__ vorbis_enc_residue ;
struct TYPE_9__ {TYPE_3__* codebooks; } ;
typedef  TYPE_2__ vorbis_enc_context ;
struct TYPE_10__ {int ndimensions; } ;
typedef  TYPE_3__ vorbis_enc_codebook ;
typedef  int /*<<< orphan*/  PutBitContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EINVAL ; 
 float FFMAX (float,int /*<<< orphan*/ ) ; 
 int MAX_CHANNELS ; 
 int MAX_CODEBOOK_DIM ; 
 int NUM_RESIDUE_PARTITIONS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int /*<<< orphan*/  fabs (float) ; 
 scalar_t__ put_codeword (int /*<<< orphan*/ *,TYPE_3__*,int) ; 
 float* put_vector (TYPE_3__*,int /*<<< orphan*/ *,float*) ; 

__attribute__((used)) static int residue_encode(vorbis_enc_context *venc, vorbis_enc_residue *rc,
                          PutBitContext *pb, float *coeffs, int samples,
                          int real_ch)
{
    int pass, i, j, p, k;
    int psize      = rc->partition_size;
    int partitions = (rc->end - rc->begin) / psize;
    int channels   = (rc->type == 2) ? 1 : real_ch;
    int classes[MAX_CHANNELS][NUM_RESIDUE_PARTITIONS];
    int classwords = venc->codebooks[rc->classbook].ndimensions;

    av_assert0(rc->type == 2);
    av_assert0(real_ch == 2);
    for (p = 0; p < partitions; p++) {
        float max1 = 0.0, max2 = 0.0;
        int s = rc->begin + p * psize;
        for (k = s; k < s + psize; k += 2) {
            max1 = FFMAX(max1, fabs(coeffs[          k / real_ch]));
            max2 = FFMAX(max2, fabs(coeffs[samples + k / real_ch]));
        }

        for (i = 0; i < rc->classifications - 1; i++)
            if (max1 < rc->maxes[i][0] && max2 < rc->maxes[i][1])
                break;
        classes[0][p] = i;
    }

    for (pass = 0; pass < 8; pass++) {
        p = 0;
        while (p < partitions) {
            if (pass == 0)
                for (j = 0; j < channels; j++) {
                    vorbis_enc_codebook * book = &venc->codebooks[rc->classbook];
                    int entry = 0;
                    for (i = 0; i < classwords; i++) {
                        entry *= rc->classifications;
                        entry += classes[j][p + i];
                    }
                    if (put_codeword(pb, book, entry))
                        return AVERROR(EINVAL);
                }
            for (i = 0; i < classwords && p < partitions; i++, p++) {
                for (j = 0; j < channels; j++) {
                    int nbook = rc->books[classes[j][p]][pass];
                    vorbis_enc_codebook * book = &venc->codebooks[nbook];
                    float *buf = coeffs + samples*j + rc->begin + p*psize;
                    if (nbook == -1)
                        continue;

                    assert(rc->type == 0 || rc->type == 2);
                    assert(!(psize % book->ndimensions));

                    if (rc->type == 0) {
                        for (k = 0; k < psize; k += book->ndimensions) {
                            int l;
                            float *a = put_vector(book, pb, &buf[k]);
                            if (!a)
                                return AVERROR(EINVAL);
                            for (l = 0; l < book->ndimensions; l++)
                                buf[k + l] -= a[l];
                        }
                    } else {
                        int s = rc->begin + p * psize, a1, b1;
                        a1 = (s % real_ch) * samples;
                        b1 =  s / real_ch;
                        s  = real_ch * samples;
                        for (k = 0; k < psize; k += book->ndimensions) {
                            int dim, a2 = a1, b2 = b1;
                            float vec[MAX_CODEBOOK_DIM], *pv = vec;
                            for (dim = book->ndimensions; dim--; ) {
                                *pv++ = coeffs[a2 + b2];
                                if ((a2 += samples) == s) {
                                    a2 = 0;
                                    b2++;
                                }
                            }
                            pv = put_vector(book, pb, vec);
                            if (!pv)
                                return AVERROR(EINVAL);
                            for (dim = book->ndimensions; dim--; ) {
                                coeffs[a1 + b1] -= *pv++;
                                if ((a1 += samples) == s) {
                                    a1 = 0;
                                    b1++;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return 0;
}