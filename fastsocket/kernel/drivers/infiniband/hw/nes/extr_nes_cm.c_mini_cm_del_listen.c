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
struct nes_cm_listener {int /*<<< orphan*/ * cm_id; int /*<<< orphan*/  listener_state; } ;
struct nes_cm_core {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NES_CM_LISTENER_PASSIVE_STATE ; 
 int mini_cm_dec_refcnt_listen (struct nes_cm_core*,struct nes_cm_listener*,int) ; 

__attribute__((used)) static int mini_cm_del_listen(struct nes_cm_core *cm_core,
			      struct nes_cm_listener *listener)
{
	listener->listener_state = NES_CM_LISTENER_PASSIVE_STATE;
	listener->cm_id = NULL; /* going to be destroyed pretty soon */
	return mini_cm_dec_refcnt_listen(cm_core, listener, 1);
}