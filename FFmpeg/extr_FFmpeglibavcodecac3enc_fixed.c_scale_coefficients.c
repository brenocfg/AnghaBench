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
struct TYPE_7__ {int /*<<< orphan*/ * coeff_shift; int /*<<< orphan*/ * mdct_coef; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* ac3_rshift_int32 ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_6__ {int num_blocks; int channels; TYPE_1__ ac3dsp; TYPE_3__* blocks; } ;
typedef  TYPE_2__ AC3EncodeContext ;
typedef  TYPE_3__ AC3Block ;

/* Variables and functions */
 int /*<<< orphan*/  AC3_MAX_COEFS ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void scale_coefficients(AC3EncodeContext *s)
{
    int blk, ch;

    for (blk = 0; blk < s->num_blocks; blk++) {
        AC3Block *block = &s->blocks[blk];
        for (ch = 1; ch <= s->channels; ch++) {
            s->ac3dsp.ac3_rshift_int32(block->mdct_coef[ch], AC3_MAX_COEFS,
                                       block->coeff_shift[ch]);
        }
    }
}