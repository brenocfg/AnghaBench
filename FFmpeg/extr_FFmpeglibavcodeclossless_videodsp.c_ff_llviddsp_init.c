#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  add_gradient_pred; int /*<<< orphan*/  add_left_pred_int16; int /*<<< orphan*/  add_left_pred; int /*<<< orphan*/  add_median_pred; int /*<<< orphan*/  add_bytes; } ;
typedef  TYPE_1__ LLVidDSPContext ;

/* Variables and functions */
 scalar_t__ ARCH_PPC ; 
 scalar_t__ ARCH_X86 ; 
 int /*<<< orphan*/  add_bytes_c ; 
 int /*<<< orphan*/  add_gradient_pred_c ; 
 int /*<<< orphan*/  add_left_pred_c ; 
 int /*<<< orphan*/  add_left_pred_int16_c ; 
 int /*<<< orphan*/  add_median_pred_c ; 
 int /*<<< orphan*/  ff_llviddsp_init_ppc (TYPE_1__*) ; 
 int /*<<< orphan*/  ff_llviddsp_init_x86 (TYPE_1__*) ; 

void ff_llviddsp_init(LLVidDSPContext *c)
{
    c->add_bytes                  = add_bytes_c;
    c->add_median_pred            = add_median_pred_c;
    c->add_left_pred              = add_left_pred_c;

    c->add_left_pred_int16        = add_left_pred_int16_c;
    c->add_gradient_pred          = add_gradient_pred_c;

    if (ARCH_PPC)
        ff_llviddsp_init_ppc(c);
    if (ARCH_X86)
        ff_llviddsp_init_x86(c);
}