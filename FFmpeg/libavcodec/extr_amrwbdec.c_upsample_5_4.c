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
struct TYPE_3__ {float (* dot_productf ) (float const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ CELPMContext ;

/* Variables and functions */
 float const* UPS_FIR_SIZE ; 
 int /*<<< orphan*/  UPS_MEM_SIZE ; 
 float stub1 (float const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * upsample_fir ; 

__attribute__((used)) static void upsample_5_4(float *out, const float *in, int o_size, CELPMContext *ctx)
{
    const float *in0 = in - UPS_FIR_SIZE + 1;
    int i, j, k;
    int int_part = 0, frac_part;

    i = 0;
    for (j = 0; j < o_size / 5; j++) {
        out[i] = in[int_part];
        frac_part = 4;
        i++;

        for (k = 1; k < 5; k++) {
            out[i] = ctx->dot_productf(in0 + int_part,
                                                  upsample_fir[4 - frac_part],
                                                  UPS_MEM_SIZE);
            int_part++;
            frac_part--;
            i++;
        }
    }
}