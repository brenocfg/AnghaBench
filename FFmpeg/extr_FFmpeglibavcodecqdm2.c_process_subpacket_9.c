#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {size_t coeff_per_sb_select; int nb_channels; int*** quantized_coeffs; int /*<<< orphan*/  sub_sampling; } ;
struct TYPE_7__ {TYPE_1__* packet; } ;
struct TYPE_6__ {int size; int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ QDM2SubPNode ;
typedef  TYPE_3__ QDM2Context ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int QDM2_SB_USED (int /*<<< orphan*/ ) ; 
 int** coeff_per_sb_for_avg ; 
 int /*<<< orphan*/  init_get_bits (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int qdm2_get_se_vlc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int qdm2_get_vlc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vlc_tab_diff ; 
 int /*<<< orphan*/  vlc_tab_level ; 
 int /*<<< orphan*/  vlc_tab_run ; 

__attribute__((used)) static int process_subpacket_9(QDM2Context *q, QDM2SubPNode *node)
{
    GetBitContext gb;
    int i, j, k, n, ch, run, level, diff;

    init_get_bits(&gb, node->packet->data, node->packet->size * 8);

    n = coeff_per_sb_for_avg[q->coeff_per_sb_select][QDM2_SB_USED(q->sub_sampling) - 1] + 1;

    for (i = 1; i < n; i++)
        for (ch = 0; ch < q->nb_channels; ch++) {
            level = qdm2_get_vlc(&gb, &vlc_tab_level, 0, 2);
            q->quantized_coeffs[ch][i][0] = level;

            for (j = 0; j < (8 - 1); ) {
                run  = qdm2_get_vlc(&gb, &vlc_tab_run, 0, 1) + 1;
                diff = qdm2_get_se_vlc(&vlc_tab_diff, &gb, 2);

                if (j + run >= 8)
                    return -1;

                for (k = 1; k <= run; k++)
                    q->quantized_coeffs[ch][i][j + k] = (level + ((k * diff) / run));

                level += diff;
                j     += run;
            }
        }

    for (ch = 0; ch < q->nb_channels; ch++)
        for (i = 0; i < 8; i++)
            q->quantized_coeffs[ch][0][i] = 0;

    return 0;
}