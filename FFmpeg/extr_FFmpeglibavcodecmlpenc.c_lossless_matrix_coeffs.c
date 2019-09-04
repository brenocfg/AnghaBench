#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  enum MLPChMode { ____Placeholder_MLPChMode } MLPChMode ;
struct TYPE_7__ {int count; int* outch; int** coeff; int** forco; unsigned int* shift; } ;
struct TYPE_9__ {TYPE_1__ matrix_params; } ;
struct TYPE_8__ {int num_channels; TYPE_3__* cur_decoding_params; } ;
typedef  TYPE_1__ MatrixParams ;
typedef  TYPE_2__ MLPEncodeContext ;
typedef  TYPE_3__ DecodingParams ;

/* Variables and functions */
#define  MLP_CHMODE_LEFT_RIGHT 131 
#define  MLP_CHMODE_LEFT_SIDE 130 
#define  MLP_CHMODE_MID_SIDE 129 
#define  MLP_CHMODE_RIGHT_SIDE 128 
 int /*<<< orphan*/  code_matrix_coeffs (TYPE_2__*,int) ; 
 int estimate_stereo_mode (TYPE_2__*) ; 

__attribute__((used)) static void lossless_matrix_coeffs(MLPEncodeContext *ctx)
{
    DecodingParams *dp = ctx->cur_decoding_params;
    MatrixParams *mp = &dp->matrix_params;
    unsigned int shift = 0;
    unsigned int channel;
    int mat;
    enum MLPChMode mode;

    /* No decorrelation for non-stereo. */
    if (ctx->num_channels - 2 != 2) {
        mp->count = 0;
        return;
    }

    mode = estimate_stereo_mode(ctx);

    switch(mode) {
        /* TODO: add matrix for MID_SIDE */
        case MLP_CHMODE_MID_SIDE:
        case MLP_CHMODE_LEFT_RIGHT:
            mp->count    = 0;
            break;
        case MLP_CHMODE_LEFT_SIDE:
            mp->count    = 1;
            mp->outch[0] = 1;
            mp->coeff[0][0] =  1 << 14; mp->coeff[0][1] = -(1 << 14);
            mp->coeff[0][2] =  0 << 14; mp->coeff[0][2] =   0 << 14;
            mp->forco[0][0] =  1 << 14; mp->forco[0][1] = -(1 << 14);
            mp->forco[0][2] =  0 << 14; mp->forco[0][2] =   0 << 14;
            break;
        case MLP_CHMODE_RIGHT_SIDE:
            mp->count    = 1;
            mp->outch[0] = 0;
            mp->coeff[0][0] =  1 << 14; mp->coeff[0][1] =   1 << 14;
            mp->coeff[0][2] =  0 << 14; mp->coeff[0][2] =   0 << 14;
            mp->forco[0][0] =  1 << 14; mp->forco[0][1] = -(1 << 14);
            mp->forco[0][2] =  0 << 14; mp->forco[0][2] =   0 << 14;
            break;
    }

    for (mat = 0; mat < mp->count; mat++)
        code_matrix_coeffs(ctx, mat);

    for (channel = 0; channel < ctx->num_channels; channel++)
        mp->shift[channel] = shift;
}