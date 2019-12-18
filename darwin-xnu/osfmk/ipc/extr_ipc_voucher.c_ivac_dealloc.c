#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_9__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  size_t natural_t ;
typedef  size_t iv_index_t ;
typedef  TYPE_1__* ipc_voucher_attr_manager_t ;
typedef  TYPE_2__* ipc_voucher_attr_control_t ;
typedef  TYPE_3__* ipc_port_t ;
struct TYPE_19__ {int /*<<< orphan*/  ivgte_key; TYPE_2__* ivgte_control; TYPE_1__* ivgte_manager; } ;
struct TYPE_18__ {scalar_t__ ivace_refs; } ;
struct TYPE_17__ {scalar_t__ ip_srights; } ;
struct TYPE_16__ {size_t ivac_key_index; size_t ivac_table_size; TYPE_6__* ivac_table; int /*<<< orphan*/  ivac_refs; TYPE_3__* ivac_port; } ;
struct TYPE_15__ {int /*<<< orphan*/  (* ivam_release ) (TYPE_1__*) ;} ;

/* Variables and functions */
 scalar_t__ IP_VALID (TYPE_3__*) ; 
 TYPE_2__* IVAC_NULL ; 
 TYPE_1__* IVAM_NULL ; 
 int /*<<< orphan*/  MACH_VOUCHER_ATTR_KEY_NONE ; 
 int /*<<< orphan*/  assert (int) ; 
 int ip_active (TYPE_3__*) ; 
 int /*<<< orphan*/  ipc_port_dealloc_kernel (TYPE_3__*) ; 
 int /*<<< orphan*/  ipc_voucher_attr_control_zone ; 
 TYPE_9__* iv_global_table ; 
 int /*<<< orphan*/  ivac_lock_destroy (TYPE_2__*) ; 
 int /*<<< orphan*/  ivgt_lock () ; 
 int /*<<< orphan*/  ivgt_unlock () ; 
 int /*<<< orphan*/  kfree (TYPE_6__*,int) ; 
 scalar_t__ os_ref_get_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ ,TYPE_2__*) ; 

void
ivac_dealloc(ipc_voucher_attr_control_t ivac)
{
	ipc_voucher_attr_manager_t ivam = IVAM_NULL;
	iv_index_t key_index = ivac->ivac_key_index;
	ipc_port_t port = ivac->ivac_port;
	natural_t i;

	/*
	 * If the control is in the global table, we
	 * have to remove it from there before we (re)confirm
	 * that the reference count is still zero.
	 */
	ivgt_lock();
	if (os_ref_get_count(&ivac->ivac_refs) > 0) {
		ivgt_unlock();
		return;
	}

	/* take it out of the global table */
	if (iv_global_table[key_index].ivgte_control == ivac) {
		ivam = iv_global_table[key_index].ivgte_manager;
		iv_global_table[key_index].ivgte_manager = IVAM_NULL;
		iv_global_table[key_index].ivgte_control = IVAC_NULL;
		iv_global_table[key_index].ivgte_key = MACH_VOUCHER_ATTR_KEY_NONE;
	}
	ivgt_unlock();

	/* release the reference held on the resource manager */
	if (IVAM_NULL != ivam)
		(ivam->ivam_release)(ivam);

	/*
	 * if a port was allocated for this voucher,
	 * it must not have any remaining send rights,
	 * because the port's reference on the voucher
	 * is gone.  We can just discard it now.
	 */
	if (IP_VALID(port)) {
		assert(ip_active(port));
		assert(port->ip_srights == 0);

		ipc_port_dealloc_kernel(port);
	}

	/*
	 * the resource manager's control reference and all references
	 * held by the specific value caches are gone, so free the
	 * table.
	 */
#ifdef MACH_DEBUG
	for (i = 0; i < ivac->ivac_table_size; i++)
		if (ivac->ivac_table[i].ivace_refs != 0)
			panic("deallocing a resource manager with live refs to its attr values\n");
#endif
	kfree(ivac->ivac_table, ivac->ivac_table_size * sizeof(*ivac->ivac_table));
	ivac_lock_destroy(ivac);
	zfree(ipc_voucher_attr_control_zone, ivac);
}