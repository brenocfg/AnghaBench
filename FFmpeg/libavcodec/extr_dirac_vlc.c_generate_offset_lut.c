#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int preamble_bits; int preamble; int sign; } ;
typedef  TYPE_1__ DiracGolombLUT ;

/* Variables and functions */
 int CONVERT_TO_RESIDUE (int,int) ; 
 int /*<<< orphan*/  INIT_RESIDUE (int) ; 
 scalar_t__ LUT_BITS ; 
 int LUT_SIZE ; 
 int RSIZE_BITS ; 
 int /*<<< orphan*/  SET_RESIDUE (int,int,scalar_t__) ; 
 int res ; 
 int /*<<< orphan*/  search_for_golomb (TYPE_1__*,int,scalar_t__) ; 

__attribute__((used)) static void generate_offset_lut(DiracGolombLUT *lut, int off)
{
    int idx;
    for (idx = 0; idx < LUT_SIZE; idx++) {
        DiracGolombLUT *l = &lut[idx];

        INIT_RESIDUE(res);
        SET_RESIDUE(res, idx, LUT_BITS);

        l->preamble_bits = off;
        if (off) {
            l->preamble  = CONVERT_TO_RESIDUE(res >> (RSIZE_BITS - off), off);
            l->sign      = ((l->preamble >> (RSIZE_BITS - l->preamble_bits)) & 1) ? -1 : +1;
        } else {
            l->preamble  = 0;
            l->sign = 1;
        }

        search_for_golomb(l, res << off, LUT_BITS - off);
    }
}