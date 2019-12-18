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
struct TYPE_4__ {int /*<<< orphan*/  acelp_apply_order_2_transfer_function; int /*<<< orphan*/  acelp_interpolatef; } ;
typedef  TYPE_1__ ACELPFContext ;

/* Variables and functions */
 scalar_t__ HAVE_MIPSFPU ; 
 int /*<<< orphan*/  ff_acelp_apply_order_2_transfer_function ; 
 int /*<<< orphan*/  ff_acelp_filter_init_mips (TYPE_1__*) ; 
 int /*<<< orphan*/  ff_acelp_interpolatef ; 

void ff_acelp_filter_init(ACELPFContext *c)
{
    c->acelp_interpolatef                      = ff_acelp_interpolatef;
    c->acelp_apply_order_2_transfer_function   = ff_acelp_apply_order_2_transfer_function;

    if(HAVE_MIPSFPU)
        ff_acelp_filter_init_mips(c);
}