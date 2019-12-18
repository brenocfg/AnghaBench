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
typedef  int /*<<< orphan*/  me_cmp_func ;
struct TYPE_3__ {int /*<<< orphan*/ * w97; int /*<<< orphan*/ * w53; int /*<<< orphan*/ * nsse; int /*<<< orphan*/ * vsse; int /*<<< orphan*/ * vsad; int /*<<< orphan*/ * rd; int /*<<< orphan*/ * bit; int /*<<< orphan*/ * quant_psnr; int /*<<< orphan*/ * dct_max; int /*<<< orphan*/ * dct264_sad; int /*<<< orphan*/ * dct_sad; int /*<<< orphan*/ * sse; int /*<<< orphan*/ * hadamard8_diff; int /*<<< orphan*/ * median_sad; int /*<<< orphan*/ * sad; } ;
typedef  TYPE_1__ MECmpContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
#define  FF_CMP_BIT 143 
#define  FF_CMP_DCT 142 
#define  FF_CMP_DCT264 141 
#define  FF_CMP_DCTMAX 140 
#define  FF_CMP_MEDIAN_SAD 139 
#define  FF_CMP_NSSE 138 
#define  FF_CMP_PSNR 137 
#define  FF_CMP_RD 136 
#define  FF_CMP_SAD 135 
#define  FF_CMP_SATD 134 
#define  FF_CMP_SSE 133 
#define  FF_CMP_VSAD 132 
#define  FF_CMP_VSSE 131 
#define  FF_CMP_W53 130 
#define  FF_CMP_W97 129 
#define  FF_CMP_ZERO 128 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zero_cmp ; 

void ff_set_cmp(MECmpContext *c, me_cmp_func *cmp, int type)
{
    int i;

    memset(cmp, 0, sizeof(void *) * 6);

    for (i = 0; i < 6; i++) {
        switch (type & 0xFF) {
        case FF_CMP_SAD:
            cmp[i] = c->sad[i];
            break;
        case FF_CMP_MEDIAN_SAD:
            cmp[i] = c->median_sad[i];
            break;
        case FF_CMP_SATD:
            cmp[i] = c->hadamard8_diff[i];
            break;
        case FF_CMP_SSE:
            cmp[i] = c->sse[i];
            break;
        case FF_CMP_DCT:
            cmp[i] = c->dct_sad[i];
            break;
        case FF_CMP_DCT264:
            cmp[i] = c->dct264_sad[i];
            break;
        case FF_CMP_DCTMAX:
            cmp[i] = c->dct_max[i];
            break;
        case FF_CMP_PSNR:
            cmp[i] = c->quant_psnr[i];
            break;
        case FF_CMP_BIT:
            cmp[i] = c->bit[i];
            break;
        case FF_CMP_RD:
            cmp[i] = c->rd[i];
            break;
        case FF_CMP_VSAD:
            cmp[i] = c->vsad[i];
            break;
        case FF_CMP_VSSE:
            cmp[i] = c->vsse[i];
            break;
        case FF_CMP_ZERO:
            cmp[i] = zero_cmp;
            break;
        case FF_CMP_NSSE:
            cmp[i] = c->nsse[i];
            break;
#if CONFIG_DWT
        case FF_CMP_W53:
            cmp[i]= c->w53[i];
            break;
        case FF_CMP_W97:
            cmp[i]= c->w97[i];
            break;
#endif
        default:
            av_log(NULL, AV_LOG_ERROR,
                   "internal error in cmp function selection\n");
        }
    }
}