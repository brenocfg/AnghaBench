#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_10__ {int /*<<< orphan*/  avctx; } ;
struct TYPE_9__ {int** s_indexmapped; int bs_num_env; size_t* bs_freq_res; int bs_num_noise; scalar_t__* t_env; scalar_t__* t_q; int* bs_add_harmonic; scalar_t__ bs_add_harmonic_flag; int /*<<< orphan*/ ** noise_facs; int /*<<< orphan*/ ** env_facs; } ;
struct TYPE_8__ {unsigned int* n; int* f_tablehigh; int* f_tablelow; int* kx; int n_q; int* f_tablenoise; int** s_mapped; int /*<<< orphan*/ ** q_mapped; int /*<<< orphan*/ ** e_origmapped; } ;
typedef  TYPE_1__ SpectralBandReplication ;
typedef  TYPE_2__ SBRData ;
typedef  TYPE_3__ AACContext ;

/* Variables and functions */
 int AVERROR_BUG ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 
 int /*<<< orphan*/  sbr_turnoff (TYPE_1__*) ; 

__attribute__((used)) static int sbr_mapping(AACContext *ac, SpectralBandReplication *sbr,
                        SBRData *ch_data, int e_a[2])
{
    int e, i, m;

    memset(ch_data->s_indexmapped[1], 0, 7*sizeof(ch_data->s_indexmapped[1]));
    for (e = 0; e < ch_data->bs_num_env; e++) {
        const unsigned int ilim = sbr->n[ch_data->bs_freq_res[e + 1]];
        uint16_t *table = ch_data->bs_freq_res[e + 1] ? sbr->f_tablehigh : sbr->f_tablelow;
        int k;

        if (sbr->kx[1] != table[0]) {
            av_log(ac->avctx, AV_LOG_ERROR, "kx != f_table{high,low}[0]. "
                   "Derived frequency tables were not regenerated.\n");
            sbr_turnoff(sbr);
            return AVERROR_BUG;
        }
        for (i = 0; i < ilim; i++)
            for (m = table[i]; m < table[i + 1]; m++)
                sbr->e_origmapped[e][m - sbr->kx[1]] = ch_data->env_facs[e+1][i];

        // ch_data->bs_num_noise > 1 => 2 noise floors
        k = (ch_data->bs_num_noise > 1) && (ch_data->t_env[e] >= ch_data->t_q[1]);
        for (i = 0; i < sbr->n_q; i++)
            for (m = sbr->f_tablenoise[i]; m < sbr->f_tablenoise[i + 1]; m++)
                sbr->q_mapped[e][m - sbr->kx[1]] = ch_data->noise_facs[k+1][i];

        for (i = 0; i < sbr->n[1]; i++) {
            if (ch_data->bs_add_harmonic_flag) {
                const unsigned int m_midpoint =
                    (sbr->f_tablehigh[i] + sbr->f_tablehigh[i + 1]) >> 1;

                ch_data->s_indexmapped[e + 1][m_midpoint - sbr->kx[1]] = ch_data->bs_add_harmonic[i] *
                    (e >= e_a[1] || (ch_data->s_indexmapped[0][m_midpoint - sbr->kx[1]] == 1));
            }
        }

        for (i = 0; i < ilim; i++) {
            int additional_sinusoid_present = 0;
            for (m = table[i]; m < table[i + 1]; m++) {
                if (ch_data->s_indexmapped[e + 1][m - sbr->kx[1]]) {
                    additional_sinusoid_present = 1;
                    break;
                }
            }
            memset(&sbr->s_mapped[e][table[i] - sbr->kx[1]], additional_sinusoid_present,
                   (table[i + 1] - table[i]) * sizeof(sbr->s_mapped[e][0]));
        }
    }

    memcpy(ch_data->s_indexmapped[0], ch_data->s_indexmapped[ch_data->bs_num_env], sizeof(ch_data->s_indexmapped[0]));
    return 0;
}