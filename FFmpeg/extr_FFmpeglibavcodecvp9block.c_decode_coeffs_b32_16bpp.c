#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_9__ {TYPE_3__* s; int /*<<< orphan*/  c; } ;
typedef  TYPE_4__ VP9TileData ;
struct TYPE_6__ {int /*<<< orphan*/  bpp; } ;
struct TYPE_7__ {TYPE_1__ h; } ;
struct TYPE_8__ {TYPE_2__ s; } ;

/* Variables and functions */
 int decode_coeffs_b_generic (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int***,unsigned int***,int /*<<< orphan*/ ***,int,int /*<<< orphan*/  const*,int /*<<< orphan*/  const**,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int decode_coeffs_b32_16bpp(VP9TileData *td, int16_t *coef, int n_coeffs,
                                   unsigned (*cnt)[6][3], unsigned (*eob)[6][2],
                                   uint8_t (*p)[6][11], int nnz, const int16_t *scan,
                                   const int16_t (*nb)[2], const int16_t *band_counts,
                                   int16_t *qmul)
{
    return decode_coeffs_b_generic(td->c, coef, n_coeffs, 1, 0, td->s->s.h.bpp, cnt, eob, p,
                                   nnz, scan, nb, band_counts, qmul);
}