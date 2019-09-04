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
typedef  int /*<<< orphan*/  int16_t ;
typedef  int /*<<< orphan*/  RA144Context ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int /*<<< orphan*/  ff_subblock_synthesis (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int,int,int,int,int) ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void do_output_subblock(RA144Context *ractx, const int16_t  *lpc_coefs,
                               int gval, GetBitContext *gb)
{
    int cba_idx = get_bits(gb, 7); // index of the adaptive CB, 0 if none
    int gain    = get_bits(gb, 8);
    int cb1_idx = get_bits(gb, 7);
    int cb2_idx = get_bits(gb, 7);

    ff_subblock_synthesis(ractx, lpc_coefs, cba_idx, cb1_idx, cb2_idx, gval,
                          gain);
}