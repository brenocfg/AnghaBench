#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* mig_object_t ;
typedef  TYPE_3__* ipc_port_t ;
struct TYPE_13__ {scalar_t__ ip_kobject; } ;
struct TYPE_12__ {TYPE_1__* pVtbl; } ;
struct TYPE_11__ {int /*<<< orphan*/  (* QueryInterface ) (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,void**) ;} ;
typedef  int /*<<< orphan*/  MIGIID ;
typedef  int /*<<< orphan*/  IMIGObject ;

/* Variables and functions */
 scalar_t__ IKOT_MIG ; 
 int /*<<< orphan*/  IP_VALID (TYPE_3__*) ; 
 int /*<<< orphan*/  ip_active (TYPE_3__*) ; 
 scalar_t__ ip_kotype (TYPE_3__*) ; 
 int /*<<< orphan*/  ip_lock (TYPE_3__*) ; 
 int /*<<< orphan*/  ip_unlock (TYPE_3__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,void**) ; 

mig_object_t
convert_port_to_mig_object(
	ipc_port_t	port,
	const MIGIID	*iid)
{
	mig_object_t	mig_object;
	void 		*ppv;

	if (!IP_VALID(port))
		return NULL;

	ip_lock(port);
	if (!ip_active(port) || (ip_kotype(port) != IKOT_MIG)) {
		ip_unlock(port);
		return NULL;
	}

	/*
	 * Our port points to some MIG object interface.  Now
	 * query it to get a reference to the desired interface.
	 */
	ppv = NULL;
	mig_object = (mig_object_t)port->ip_kobject;
	mig_object->pVtbl->QueryInterface((IMIGObject *)mig_object, iid, &ppv);
	ip_unlock(port);
	return (mig_object_t)ppv;
}