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
typedef  int /*<<< orphan*/  int32_t ;
typedef  int int16_t ;
struct TYPE_3__ {int in_channels; int out_channels; int /*<<< orphan*/  (* downmix_fixed ) (int /*<<< orphan*/ **,int**,int) ;} ;
typedef  TYPE_1__ AC3DSPContext ;

/* Variables and functions */
 int /*<<< orphan*/  ac3_downmix_5_to_1_symmetric_c_fixed (int /*<<< orphan*/ **,int**,int) ; 
 int /*<<< orphan*/  ac3_downmix_5_to_2_symmetric_c_fixed (int /*<<< orphan*/ **,int**,int) ; 
 int /*<<< orphan*/  ac3_downmix_c_fixed (int /*<<< orphan*/ **,int**,int,int,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ **,int**,int) ; 

void ff_ac3dsp_downmix_fixed(AC3DSPContext *c, int32_t **samples, int16_t **matrix,
                             int out_ch, int in_ch, int len)
{
    if (c->in_channels != in_ch || c->out_channels != out_ch) {
        c->in_channels  = in_ch;
        c->out_channels = out_ch;
        c->downmix_fixed = NULL;

        if (in_ch == 5 && out_ch == 2 &&
            !(matrix[1][0] | matrix[0][2]  |
              matrix[1][3] | matrix[0][4]  |
             (matrix[0][1] ^ matrix[1][1]) |
             (matrix[0][0] ^ matrix[1][2]))) {
            c->downmix_fixed = ac3_downmix_5_to_2_symmetric_c_fixed;
        } else if (in_ch == 5 && out_ch == 1 &&
                   matrix[0][0] == matrix[0][2] &&
                   matrix[0][3] == matrix[0][4]) {
            c->downmix_fixed = ac3_downmix_5_to_1_symmetric_c_fixed;
        }
    }

    if (c->downmix_fixed)
        c->downmix_fixed(samples, matrix, len);
    else
        ac3_downmix_c_fixed(samples, matrix, out_ch, in_ch, len);
}