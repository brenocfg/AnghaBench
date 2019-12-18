#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int int16_t ;
typedef  enum TxfmType { ____Placeholder_TxfmType } TxfmType ;
typedef  enum TxfmMode { ____Placeholder_TxfmMode } TxfmMode ;

/* Variables and functions */
 int /*<<< orphan*/  AV_COPY32 (int*,int const*) ; 
 int /*<<< orphan*/  AV_ZERO32 (int*) ; 
 int*** ff_vp9_scans ; 

__attribute__((used)) static int copy_subcoefs(int16_t *out, const int16_t *in, enum TxfmMode tx,
                         enum TxfmType txtp, int sz, int sub, int bit_depth)
{
    // copy the topleft coefficients such that the return value (being the
    // coefficient scantable index for the eob token) guarantees that only
    // the topleft $sub out of $sz (where $sz >= $sub) coefficients in both
    // dimensions are non-zero. This leads to braching to specific optimized
    // simd versions (e.g. dc-only) so that we get full asm coverage in this
    // test

    int n;
    const int16_t *scan = ff_vp9_scans[tx][txtp];
    int eob;

    for (n = 0; n < sz * sz; n++) {
        int rc = scan[n], rcx = rc % sz, rcy = rc / sz;

        // find eob for this sub-idct
        if (rcx >= sub || rcy >= sub)
            break;

        // copy coef
        if (bit_depth == 8) {
            out[rc] = in[rc];
        } else {
            AV_COPY32(&out[rc * 2], &in[rc * 2]);
        }
    }

    eob = n;

    for (; n < sz * sz; n++) {
        int rc = scan[n];

        // zero
        if (bit_depth == 8) {
            out[rc] = 0;
        } else {
            AV_ZERO32(&out[rc * 2]);
        }
    }

    return eob;
}