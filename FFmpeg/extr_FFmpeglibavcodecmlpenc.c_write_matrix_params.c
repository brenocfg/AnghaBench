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
typedef  int int32_t ;
struct TYPE_5__ {int count; int* outch; int* fbits; int** coeff; } ;
struct TYPE_7__ {TYPE_1__ matrix_params; } ;
struct TYPE_6__ {unsigned int num_channels; TYPE_3__* cur_decoding_params; } ;
typedef  int /*<<< orphan*/  PutBitContext ;
typedef  TYPE_1__ MatrixParams ;
typedef  TYPE_2__ MLPEncodeContext ;
typedef  TYPE_3__ DecodingParams ;

/* Variables and functions */
 int /*<<< orphan*/  put_bits (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  put_sbits (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void write_matrix_params(MLPEncodeContext *ctx, PutBitContext *pb)
{
    DecodingParams *dp = ctx->cur_decoding_params;
    MatrixParams *mp = &dp->matrix_params;
    unsigned int mat;

    put_bits(pb, 4, mp->count);

    for (mat = 0; mat < mp->count; mat++) {
        unsigned int channel;

        put_bits(pb, 4, mp->outch[mat]); /* matrix_out_ch */
        put_bits(pb, 4, mp->fbits[mat]);
        put_bits(pb, 1, 0             ); /* lsb_bypass */

        for (channel = 0; channel < ctx->num_channels; channel++) {
            int32_t coeff = mp->coeff[mat][channel];

            if (coeff) {
                put_bits(pb, 1, 1);

                coeff >>= 14 - mp->fbits[mat];

                put_sbits(pb, mp->fbits[mat] + 2, coeff);
            } else {
                put_bits(pb, 1, 0);
            }
        }
    }
}