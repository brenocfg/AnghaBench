#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct atm_vcc {int /*<<< orphan*/  send; int /*<<< orphan*/ * push_oam; int /*<<< orphan*/  pop; int /*<<< orphan*/  push; } ;

/* Variables and functions */
 int /*<<< orphan*/  atm_pop_raw ; 
 int /*<<< orphan*/  atm_push_raw ; 
 int /*<<< orphan*/  atm_send_aal0 ; 

int atm_init_aal0(struct atm_vcc *vcc)
{
	vcc->push = atm_push_raw;
	vcc->pop = atm_pop_raw;
	vcc->push_oam = NULL;
	vcc->send = atm_send_aal0;
	return 0;
}