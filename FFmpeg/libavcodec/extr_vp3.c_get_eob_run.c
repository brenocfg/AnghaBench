#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int base; scalar_t__ bits; } ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 TYPE_1__* eob_run_table ; 
 scalar_t__ get_bits (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static inline int get_eob_run(GetBitContext *gb, int token)
{
    int v = eob_run_table[token].base;
    if (eob_run_table[token].bits)
        v += get_bits(gb, eob_run_table[token].bits);
    return v;
}