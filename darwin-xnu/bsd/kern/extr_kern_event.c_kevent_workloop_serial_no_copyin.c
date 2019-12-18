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
typedef  scalar_t__ user_addr_t ;
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  serial_no32 ;
typedef  int /*<<< orphan*/  serial_no ;
typedef  TYPE_1__* proc_t ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_4__ {scalar_t__ p_dispatchqueue_serialno_offset; } ;

/* Variables and functions */
 int copyin (scalar_t__,int /*<<< orphan*/ ,int) ; 
 scalar_t__ proc_is64bit (TYPE_1__*) ; 

__attribute__((used)) static uint64_t
kevent_workloop_serial_no_copyin(proc_t p, uint64_t workloop_id)
{
	uint64_t serial_no = 0;
	user_addr_t addr;
	int rc;

	if (workloop_id == 0 || p->p_dispatchqueue_serialno_offset == 0) {
		return 0;
	}
	addr = (user_addr_t)(workloop_id + p->p_dispatchqueue_serialno_offset);

	if (proc_is64bit(p)) {
		rc = copyin(addr, (caddr_t)&serial_no, sizeof(serial_no));
	} else {
		uint32_t serial_no32 = 0;
		rc = copyin(addr, (caddr_t)&serial_no32, sizeof(serial_no32));
		serial_no = serial_no32;
	}
	return rc == 0 ? serial_no : 0;
}