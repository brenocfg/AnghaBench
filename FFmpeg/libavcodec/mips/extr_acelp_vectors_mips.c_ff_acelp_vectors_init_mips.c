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
struct TYPE_3__ {int /*<<< orphan*/  weighted_vector_sumf; } ;
typedef  TYPE_1__ ACELPVContext ;

/* Variables and functions */
 int /*<<< orphan*/  ff_weighted_vector_sumf_mips ; 

void ff_acelp_vectors_init_mips(ACELPVContext *c)
{
#if HAVE_INLINE_ASM
#if !HAVE_MIPS32R6 && !HAVE_MIPS64R6
    c->weighted_vector_sumf = ff_weighted_vector_sumf_mips;
#endif
#endif
}