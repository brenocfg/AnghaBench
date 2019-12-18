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
struct TYPE_4__ {int /*<<< orphan*/  celp_lp_zero_synthesis_filterf; int /*<<< orphan*/  celp_lp_synthesis_filterf; } ;
typedef  TYPE_1__ CELPFContext ;

/* Variables and functions */
 scalar_t__ HAVE_MIPSFPU ; 
 int /*<<< orphan*/  ff_celp_filter_init_mips (TYPE_1__*) ; 
 int /*<<< orphan*/  ff_celp_lp_synthesis_filterf ; 
 int /*<<< orphan*/  ff_celp_lp_zero_synthesis_filterf ; 

void ff_celp_filter_init(CELPFContext *c)
{
    c->celp_lp_synthesis_filterf        = ff_celp_lp_synthesis_filterf;
    c->celp_lp_zero_synthesis_filterf   = ff_celp_lp_zero_synthesis_filterf;

    if(HAVE_MIPSFPU)
        ff_celp_filter_init_mips(c);
}