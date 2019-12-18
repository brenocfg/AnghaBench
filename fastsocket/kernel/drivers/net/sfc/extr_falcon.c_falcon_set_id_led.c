#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct efx_nic {int dummy; } ;
typedef  enum efx_led_mode { ____Placeholder_efx_led_mode } efx_led_mode ;
struct TYPE_4__ {TYPE_1__* type; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* set_id_led ) (struct efx_nic*,int) ;} ;

/* Variables and functions */
 TYPE_2__* falcon_board (struct efx_nic*) ; 
 int /*<<< orphan*/  stub1 (struct efx_nic*,int) ; 

__attribute__((used)) static void falcon_set_id_led(struct efx_nic *efx, enum efx_led_mode mode)
{
	falcon_board(efx)->type->set_id_led(efx, mode);
}