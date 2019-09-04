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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_3__ {int /*<<< orphan*/  c; } ;
typedef  TYPE_1__ VP9TileData ;

/* Variables and functions */
 int decode_coeffs_b_generic (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int,unsigned int***,unsigned int***,int /*<<< orphan*/ ***,int,int /*<<< orphan*/  const*,int /*<<< orphan*/  const**,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int decode_coeffs_b_8bpp(VP9TileData *td, int16_t *coef, int n_coeffs,
                                unsigned (*cnt)[6][3], unsigned (*eob)[6][2],
                                uint8_t (*p)[6][11], int nnz, const int16_t *scan,
                                const int16_t (*nb)[2], const int16_t *band_counts,
                                int16_t *qmul)
{
    return decode_coeffs_b_generic(td->c, coef, n_coeffs, 0, 1, 8, cnt, eob, p,
                                   nnz, scan, nb, band_counts, qmul);
}