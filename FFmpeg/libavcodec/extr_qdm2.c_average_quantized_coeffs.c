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
struct TYPE_3__ {size_t coeff_per_sb_select; int nb_channels; int*** quantized_coeffs; int /*<<< orphan*/  sub_sampling; } ;
typedef  TYPE_1__ QDM2Context ;

/* Variables and functions */
 int QDM2_SB_USED (int /*<<< orphan*/ ) ; 
 int** coeff_per_sb_for_avg ; 

__attribute__((used)) static void average_quantized_coeffs(QDM2Context *q)
{
    int i, j, n, ch, sum;

    n = coeff_per_sb_for_avg[q->coeff_per_sb_select][QDM2_SB_USED(q->sub_sampling) - 1] + 1;

    for (ch = 0; ch < q->nb_channels; ch++)
        for (i = 0; i < n; i++) {
            sum = 0;

            for (j = 0; j < 8; j++)
                sum += q->quantized_coeffs[ch][i][j];

            sum /= 8;
            if (sum > 0)
                sum--;

            for (j = 0; j < 8; j++)
                q->quantized_coeffs[ch][i][j] = sum;
        }
}