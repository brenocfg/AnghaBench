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
typedef  int /*<<< orphan*/  premultiplied_coeffs ;
typedef  scalar_t__ int64_t ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_3__ {int /*<<< orphan*/ * private_data; } ;
typedef  TYPE_1__ DCAADPCMEncContext ;

/* Variables and functions */
 int DCA_ADPCM_COEFFS ; 
 int DCA_ADPCM_VQCODEBOOK_SZ ; 
 scalar_t__ apply_filter (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/  const) ; 
 scalar_t__ calc_corr (int /*<<< orphan*/  const*,int,int,int) ; 
 int /*<<< orphan*/ * ff_dca_adpcm_vb ; 

__attribute__((used)) static int64_t find_best_filter(const DCAADPCMEncContext *s, const int32_t *in, int len)
{
    const premultiplied_coeffs *precalc_data = s->private_data;
    int i, j, k = 0;
    int vq = -1;
    int64_t err;
    int64_t min_err = 1ll << 62;
    int64_t corr[15];

    for (i = 0; i <= DCA_ADPCM_COEFFS; i++)
        for (j = i; j <= DCA_ADPCM_COEFFS; j++)
            corr[k++] = calc_corr(in+4, len, i, j);

    for (i = 0; i < DCA_ADPCM_VQCODEBOOK_SZ; i++) {
        err = apply_filter(ff_dca_adpcm_vb[i], corr, *precalc_data);
        if (err < min_err) {
            min_err = err;
            vq = i;
        }
        precalc_data++;
    }

    return vq;
}