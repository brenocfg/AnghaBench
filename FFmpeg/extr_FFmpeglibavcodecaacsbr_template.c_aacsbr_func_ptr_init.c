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
struct TYPE_4__ {int /*<<< orphan*/  sbr_hf_inverse_filter; int /*<<< orphan*/  sbr_x_gen; int /*<<< orphan*/  sbr_hf_assemble; int /*<<< orphan*/  sbr_lf_gen; } ;
typedef  TYPE_1__ AACSBRContext ;

/* Variables and functions */
 scalar_t__ ARCH_MIPS ; 
 int /*<<< orphan*/  ff_aacsbr_func_ptr_init_mips (TYPE_1__*) ; 
 int /*<<< orphan*/  sbr_hf_assemble ; 
 int /*<<< orphan*/  sbr_hf_inverse_filter ; 
 int /*<<< orphan*/  sbr_lf_gen ; 
 int /*<<< orphan*/  sbr_x_gen ; 

__attribute__((used)) static void aacsbr_func_ptr_init(AACSBRContext *c)
{
    c->sbr_lf_gen            = sbr_lf_gen;
    c->sbr_hf_assemble       = sbr_hf_assemble;
    c->sbr_x_gen             = sbr_x_gen;
    c->sbr_hf_inverse_filter = sbr_hf_inverse_filter;

#if !USE_FIXED
    if(ARCH_MIPS)
        ff_aacsbr_func_ptr_init_mips(c);
#endif
}