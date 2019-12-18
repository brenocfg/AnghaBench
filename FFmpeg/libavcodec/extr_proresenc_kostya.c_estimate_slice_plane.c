#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  ptrdiff_t ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_6__ {int /*<<< orphan*/  scantable; } ;
struct TYPE_5__ {int /*<<< orphan*/ * blocks; } ;
typedef  TYPE_1__ ProresThreadData ;
typedef  TYPE_2__ ProresContext ;

/* Variables and functions */
 int FFALIGN (int,int) ; 
 scalar_t__ estimate_acs (int*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int estimate_dcs (int*,int /*<<< orphan*/ ,int,int /*<<< orphan*/  const) ; 

__attribute__((used)) static int estimate_slice_plane(ProresContext *ctx, int *error, int plane,
                                const uint16_t *src, ptrdiff_t linesize,
                                int mbs_per_slice,
                                int blocks_per_mb, int plane_size_factor,
                                const int16_t *qmat, ProresThreadData *td)
{
    int blocks_per_slice;
    int bits;

    blocks_per_slice = mbs_per_slice * blocks_per_mb;

    bits  = estimate_dcs(error, td->blocks[plane], blocks_per_slice, qmat[0]);
    bits += estimate_acs(error, td->blocks[plane], blocks_per_slice,
                         plane_size_factor, ctx->scantable, qmat);

    return FFALIGN(bits, 8);
}