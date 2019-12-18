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
struct TYPE_4__ {int /*<<< orphan*/  weighted_vector_sumf; } ;
typedef  TYPE_1__ ACELPVContext ;

/* Variables and functions */
 scalar_t__ HAVE_MIPSFPU ; 
 int /*<<< orphan*/  ff_acelp_vectors_init_mips (TYPE_1__*) ; 
 int /*<<< orphan*/  ff_weighted_vector_sumf ; 

void ff_acelp_vectors_init(ACELPVContext *c)
{
    c->weighted_vector_sumf   = ff_weighted_vector_sumf;

    if(HAVE_MIPSFPU)
        ff_acelp_vectors_init_mips(c);
}