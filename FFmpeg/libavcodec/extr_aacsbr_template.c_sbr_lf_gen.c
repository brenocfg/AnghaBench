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
struct TYPE_3__ {int* kx; } ;
typedef  TYPE_1__ SpectralBandReplication ;
typedef  int /*<<< orphan*/  INTFLOAT ;
typedef  int /*<<< orphan*/  AACContext ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ***,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int sbr_lf_gen(AACContext *ac, SpectralBandReplication *sbr,
                      INTFLOAT X_low[32][40][2], const INTFLOAT W[2][32][32][2],
                      int buf_idx)
{
    int i, k;
    const int t_HFGen = 8;
    const int i_f = 32;
    memset(X_low, 0, 32*sizeof(*X_low));
    for (k = 0; k < sbr->kx[1]; k++) {
        for (i = t_HFGen; i < i_f + t_HFGen; i++) {
            X_low[k][i][0] = W[buf_idx][i - t_HFGen][k][0];
            X_low[k][i][1] = W[buf_idx][i - t_HFGen][k][1];
        }
    }
    buf_idx = 1-buf_idx;
    for (k = 0; k < sbr->kx[0]; k++) {
        for (i = 0; i < t_HFGen; i++) {
            X_low[k][i][0] = W[buf_idx][i + i_f - t_HFGen][k][0];
            X_low[k][i][1] = W[buf_idx][i + i_f - t_HFGen][k][1];
        }
    }
    return 0;
}