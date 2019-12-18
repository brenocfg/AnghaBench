#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int mps_pset; int mps_srights; int mps_pdrequest; int mps_nsrequest; int /*<<< orphan*/  mps_flags; int /*<<< orphan*/  mps_sorights; int /*<<< orphan*/  mps_mscount; int /*<<< orphan*/  mps_msgcount; int /*<<< orphan*/  mps_qlimit; int /*<<< orphan*/  mps_seqno; } ;
typedef  TYPE_1__ mach_port_status_t ;
typedef  TYPE_2__* ipc_port_t ;
struct TYPE_9__ {int /*<<< orphan*/  imq_msgcount; int /*<<< orphan*/  imq_qlimit; int /*<<< orphan*/  imq_seqno; } ;
struct TYPE_8__ {scalar_t__ ip_srights; scalar_t__ ip_pdrequest; scalar_t__ ip_nsrequest; scalar_t__ ip_imp_task; scalar_t__ ip_strict_guard; scalar_t__ ip_guarded; scalar_t__ ip_tempowner; scalar_t__ ip_impdonation; int /*<<< orphan*/  ip_sorights; int /*<<< orphan*/  ip_mscount; TYPE_5__ ip_messages; int /*<<< orphan*/  ip_in_pset; } ;

/* Variables and functions */
 scalar_t__ IIT_NULL ; 
 scalar_t__ IP_NULL ; 
 int /*<<< orphan*/  MACH_PORT_STATUS_FLAG_GUARDED ; 
 int /*<<< orphan*/  MACH_PORT_STATUS_FLAG_IMP_DONATION ; 
 int /*<<< orphan*/  MACH_PORT_STATUS_FLAG_STRICT_GUARD ; 
 int /*<<< orphan*/  MACH_PORT_STATUS_FLAG_TASKPTR ; 
 int /*<<< orphan*/  MACH_PORT_STATUS_FLAG_TEMPOWNER ; 
 int /*<<< orphan*/  imq_lock (TYPE_5__*) ; 
 int /*<<< orphan*/  imq_unlock (TYPE_5__*) ; 

void mach_port_get_status_helper(
	ipc_port_t		port,
	mach_port_status_t	*statusp)
{
	imq_lock(&port->ip_messages);
	/* don't leak set IDs, just indicate that the port is in one or not */
	statusp->mps_pset = !!(port->ip_in_pset);
	statusp->mps_seqno = port->ip_messages.imq_seqno;
	statusp->mps_qlimit = port->ip_messages.imq_qlimit;
	statusp->mps_msgcount = port->ip_messages.imq_msgcount;
	imq_unlock(&port->ip_messages);

	statusp->mps_mscount = port->ip_mscount;
	statusp->mps_sorights = port->ip_sorights;
	statusp->mps_srights = port->ip_srights > 0;
	statusp->mps_pdrequest = port->ip_pdrequest != IP_NULL;
	statusp->mps_nsrequest = port->ip_nsrequest != IP_NULL;
	statusp->mps_flags = 0;
	if (port->ip_impdonation) {
		statusp->mps_flags |= MACH_PORT_STATUS_FLAG_IMP_DONATION;
		if (port->ip_tempowner) {
			statusp->mps_flags |= MACH_PORT_STATUS_FLAG_TEMPOWNER;
			if (IIT_NULL != port->ip_imp_task) {
				statusp->mps_flags |= MACH_PORT_STATUS_FLAG_TASKPTR;
			}
		}
	}
	if (port->ip_guarded) {
		statusp->mps_flags |= MACH_PORT_STATUS_FLAG_GUARDED;
		if (port->ip_strict_guard) {
			statusp->mps_flags |= MACH_PORT_STATUS_FLAG_STRICT_GUARD;
		}
	}
	return;
}