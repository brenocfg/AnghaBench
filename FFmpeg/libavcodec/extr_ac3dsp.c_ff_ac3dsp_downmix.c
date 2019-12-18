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
struct TYPE_4__ {int in_channels; int out_channels; int /*<<< orphan*/  (* downmix ) (float**,float**,int) ;} ;
typedef  TYPE_1__ AC3DSPContext ;

/* Variables and functions */
 scalar_t__ ARCH_X86 ; 
 int /*<<< orphan*/  ac3_downmix_5_to_1_symmetric_c (float**,float**,int) ; 
 int /*<<< orphan*/  ac3_downmix_5_to_2_symmetric_c (float**,float**,int) ; 
 int /*<<< orphan*/  ac3_downmix_c (float**,float**,int,int,int) ; 
 int /*<<< orphan*/  ff_ac3dsp_set_downmix_x86 (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (float**,float**,int) ; 

void ff_ac3dsp_downmix(AC3DSPContext *c, float **samples, float **matrix,
                       int out_ch, int in_ch, int len)
{
    if (c->in_channels != in_ch || c->out_channels != out_ch) {
        int **matrix_cmp = (int **)matrix;

        c->in_channels  = in_ch;
        c->out_channels = out_ch;
        c->downmix      = NULL;

        if (in_ch == 5 && out_ch == 2 &&
            !(matrix_cmp[1][0] | matrix_cmp[0][2]   |
              matrix_cmp[1][3] | matrix_cmp[0][4]   |
             (matrix_cmp[0][1] ^ matrix_cmp[1][1]) |
             (matrix_cmp[0][0] ^ matrix_cmp[1][2]))) {
            c->downmix = ac3_downmix_5_to_2_symmetric_c;
        } else if (in_ch == 5 && out_ch == 1 &&
                   matrix_cmp[0][0] == matrix_cmp[0][2] &&
                   matrix_cmp[0][3] == matrix_cmp[0][4]) {
            c->downmix = ac3_downmix_5_to_1_symmetric_c;
        }

        if (ARCH_X86)
            ff_ac3dsp_set_downmix_x86(c);
    }

    if (c->downmix)
        c->downmix(samples, matrix, len);
    else
        ac3_downmix_c(samples, matrix, out_ch, in_ch, len);
}