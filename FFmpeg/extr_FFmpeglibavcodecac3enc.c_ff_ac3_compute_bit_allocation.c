#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  exponent_bits; } ;
typedef  TYPE_1__ AC3EncodeContext ;

/* Variables and functions */
 int /*<<< orphan*/  bit_alloc_masking (TYPE_1__*) ; 
 int cbr_bit_allocation (TYPE_1__*) ; 
 int /*<<< orphan*/  count_exponent_bits (TYPE_1__*) ; 
 int /*<<< orphan*/  count_frame_bits (TYPE_1__*) ; 

int ff_ac3_compute_bit_allocation(AC3EncodeContext *s)
{
    count_frame_bits(s);

    s->exponent_bits = count_exponent_bits(s);

    bit_alloc_masking(s);

    return cbr_bit_allocation(s);
}