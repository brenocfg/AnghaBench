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
struct TYPE_5__ {struct TYPE_5__* os_context; int /*<<< orphan*/  link; int /*<<< orphan*/ * adapter; } ;
typedef  TYPE_1__ divas_um_idi_entity_t ;
typedef  int /*<<< orphan*/  diva_um_idi_adapter_t ;
typedef  int /*<<< orphan*/  diva_os_spin_lock_magic_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_LOG (char*) ; 
 int /*<<< orphan*/  adapter_lock ; 
 int /*<<< orphan*/  cleanup_entity (TYPE_1__*) ; 
 int /*<<< orphan*/  diva_os_enter_spin_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  diva_os_free (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  diva_os_leave_spin_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  diva_um_idi_stop_wdog (void*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int,int) ; 

int divas_um_idi_delete_entity(int adapter_nr, void *entity)
{
	divas_um_idi_entity_t *e;
	diva_um_idi_adapter_t *a;
	diva_os_spin_lock_magic_t old_irql;

	if (!(e = (divas_um_idi_entity_t *) entity))
		return (-1);

	diva_os_enter_spin_lock(&adapter_lock, &old_irql, "delete_entity");
	if ((a = e->adapter)) {
		list_del(&e->link);
	}
	diva_os_leave_spin_lock(&adapter_lock, &old_irql, "delete_entity");

	diva_um_idi_stop_wdog(entity);
	cleanup_entity(e);
	diva_os_free(0, e->os_context);
	memset(e, 0x00, sizeof(*e));
	diva_os_free(0, e);

	DBG_LOG(("A(%d) remove E:%08x", adapter_nr, e));

	return (0);
}