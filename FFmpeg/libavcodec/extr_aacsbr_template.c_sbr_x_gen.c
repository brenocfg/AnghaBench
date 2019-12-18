#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int* kx; int* m; TYPE_1__* data; } ;
struct TYPE_4__ {int t_env_num_env_old; } ;
typedef  TYPE_2__ SpectralBandReplication ;
typedef  int /*<<< orphan*/  INTFLOAT ;

/* Variables and functions */
 int ENVELOPE_ADJUSTMENT_OFFSET ; 
 int FFMAX (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ***,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int sbr_x_gen(SpectralBandReplication *sbr, INTFLOAT X[2][38][64],
                     const INTFLOAT Y0[38][64][2], const INTFLOAT Y1[38][64][2],
                     const INTFLOAT X_low[32][40][2], int ch)
{
    int k, i;
    const int i_f = 32;
    const int i_Temp = FFMAX(2*sbr->data[ch].t_env_num_env_old - i_f, 0);
    memset(X, 0, 2*sizeof(*X));
    for (k = 0; k < sbr->kx[0]; k++) {
        for (i = 0; i < i_Temp; i++) {
            X[0][i][k] = X_low[k][i + ENVELOPE_ADJUSTMENT_OFFSET][0];
            X[1][i][k] = X_low[k][i + ENVELOPE_ADJUSTMENT_OFFSET][1];
        }
    }
    for (; k < sbr->kx[0] + sbr->m[0]; k++) {
        for (i = 0; i < i_Temp; i++) {
            X[0][i][k] = Y0[i + i_f][k][0];
            X[1][i][k] = Y0[i + i_f][k][1];
        }
    }

    for (k = 0; k < sbr->kx[1]; k++) {
        for (i = i_Temp; i < 38; i++) {
            X[0][i][k] = X_low[k][i + ENVELOPE_ADJUSTMENT_OFFSET][0];
            X[1][i][k] = X_low[k][i + ENVELOPE_ADJUSTMENT_OFFSET][1];
        }
    }
    for (; k < sbr->kx[1] + sbr->m[1]; k++) {
        for (i = i_Temp; i < i_f; i++) {
            X[0][i][k] = Y1[i][k][0];
            X[1][i][k] = Y1[i][k][1];
        }
    }
    return 0;
}