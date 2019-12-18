#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int* num_ele; int** pairing; int** index; } ;
struct TYPE_7__ {int samplerate_index; TYPE_2__ pce; } ;
struct TYPE_5__ {int flags; int profile; TYPE_3__* priv_data; } ;
typedef  int /*<<< orphan*/  PutBitContext ;
typedef  TYPE_1__ AVCodecContext ;
typedef  TYPE_2__ AACPCEInfo ;
typedef  TYPE_3__ AACEncContext ;

/* Variables and functions */
 int AV_CODEC_FLAG_BITEXACT ; 
 char* LIBAVCODEC_IDENT ; 
 int /*<<< orphan*/  avpriv_align_put_bits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avpriv_put_string (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_bits (int /*<<< orphan*/ *,int,int) ; 
 int strlen (char const*) ; 

__attribute__((used)) static void put_pce(PutBitContext *pb, AVCodecContext *avctx)
{
    int i, j;
    AACEncContext *s = avctx->priv_data;
    AACPCEInfo *pce = &s->pce;
    const int bitexact = avctx->flags & AV_CODEC_FLAG_BITEXACT;
    const char *aux_data = bitexact ? "Lavc" : LIBAVCODEC_IDENT;

    put_bits(pb, 4, 0);

    put_bits(pb, 2, avctx->profile);
    put_bits(pb, 4, s->samplerate_index);

    put_bits(pb, 4, pce->num_ele[0]); /* Front */
    put_bits(pb, 4, pce->num_ele[1]); /* Side */
    put_bits(pb, 4, pce->num_ele[2]); /* Back */
    put_bits(pb, 2, pce->num_ele[3]); /* LFE */
    put_bits(pb, 3, 0); /* Assoc data */
    put_bits(pb, 4, 0); /* CCs */

    put_bits(pb, 1, 0); /* Stereo mixdown */
    put_bits(pb, 1, 0); /* Mono mixdown */
    put_bits(pb, 1, 0); /* Something else */

    for (i = 0; i < 4; i++) {
        for (j = 0; j < pce->num_ele[i]; j++) {
            if (i < 3)
                put_bits(pb, 1, pce->pairing[i][j]);
            put_bits(pb, 4, pce->index[i][j]);
        }
    }

    avpriv_align_put_bits(pb);
    put_bits(pb, 8, strlen(aux_data));
    avpriv_put_string(pb, aux_data, 0);
}