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
struct TYPE_4__ {int /*<<< orphan*/  filter_flt; } ;
typedef  TYPE_1__ FFIIRFilterContext ;

/* Variables and functions */
 scalar_t__ HAVE_MIPSFPU ; 
 int /*<<< orphan*/  ff_iir_filter_flt ; 
 int /*<<< orphan*/  ff_iir_filter_init_mips (TYPE_1__*) ; 

void ff_iir_filter_init(FFIIRFilterContext *f) {
    f->filter_flt = ff_iir_filter_flt;

    if (HAVE_MIPSFPU)
        ff_iir_filter_init_mips(f);
}