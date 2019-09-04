#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ipc_port_t ;
typedef  TYPE_2__* ipc_kmsg_t ;
typedef  scalar_t__ ipc_importance_elem_t ;
struct TYPE_6__ {scalar_t__ ikm_importance; TYPE_1__* ikm_header; } ;
struct TYPE_5__ {int /*<<< orphan*/  msgh_remote_port; int /*<<< orphan*/  msgh_bits; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ IIE_NULL ; 
 int /*<<< orphan*/  IPID_OPTION_NORMAL ; 
 scalar_t__ IP_VALID (int /*<<< orphan*/ ) ; 
 scalar_t__ MACH_MSGH_BITS_RAISED_IMPORTANCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MACH_MSGH_BITS_RAISEIMP ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ip_active (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_unlock (int /*<<< orphan*/ ) ; 
 scalar_t__ ipc_importance_kmsg_unlink (TYPE_2__*) ; 
 int /*<<< orphan*/  ipc_importance_lock () ; 
 int /*<<< orphan*/  ipc_importance_release_locked (scalar_t__) ; 
 scalar_t__ ipc_port_importance_delta (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
ipc_importance_clean(
	ipc_kmsg_t		kmsg)
{
	ipc_port_t		port;

	/* Is the kmsg still linked? If so, remove that first */
	if (IIE_NULL != kmsg->ikm_importance) {
		ipc_importance_elem_t	elem;

		ipc_importance_lock();
		elem = ipc_importance_kmsg_unlink(kmsg);
		assert(IIE_NULL != elem);
		ipc_importance_release_locked(elem);
		/* importance unlocked */
	}

	/* See if there is a legacy importance boost to be dropped from port */
	if (MACH_MSGH_BITS_RAISED_IMPORTANCE(kmsg->ikm_header->msgh_bits)) {
		kmsg->ikm_header->msgh_bits &= ~MACH_MSGH_BITS_RAISEIMP;
		port = kmsg->ikm_header->msgh_remote_port;
		if (IP_VALID(port)) {
			ip_lock(port);
			/* inactive ports already had their importance boosts dropped */
			if (!ip_active(port) || 
			    ipc_port_importance_delta(port, IPID_OPTION_NORMAL, -1) == FALSE) {
				ip_unlock(port);
			}
		}
	}
}