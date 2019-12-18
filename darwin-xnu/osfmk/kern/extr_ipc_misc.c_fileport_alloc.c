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
struct fileglob {int dummy; } ;
typedef  scalar_t__ ipc_port_t ;
typedef  int /*<<< orphan*/  ipc_kobject_t ;

/* Variables and functions */
 int /*<<< orphan*/  IKOT_FILEPORT ; 
 scalar_t__ IP_NULL ; 
 int /*<<< orphan*/  IP_VALID (scalar_t__) ; 
 int /*<<< orphan*/  ip_lock (scalar_t__) ; 
 int /*<<< orphan*/  ipc_kobject_set (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ipc_port_alloc_kernel () ; 
 scalar_t__ ipc_port_make_send (scalar_t__) ; 
 scalar_t__ ipc_port_make_sonce_locked (scalar_t__) ; 
 int /*<<< orphan*/  ipc_port_nsrequest (scalar_t__,int,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  panic (char*) ; 

ipc_port_t
fileport_alloc(struct fileglob *fg)
{
	ipc_port_t fileport;
	ipc_port_t sendport;
	ipc_port_t notifyport;

	fileport = ipc_port_alloc_kernel();
	if (fileport == IP_NULL) {
		goto out;
	}

	ipc_kobject_set(fileport, (ipc_kobject_t)fg, IKOT_FILEPORT);
	ip_lock(fileport); /* unlocked by ipc_port_nsrequest */
	notifyport = ipc_port_make_sonce_locked(fileport);
	ipc_port_nsrequest(fileport, 1, notifyport, &notifyport);

	sendport = ipc_port_make_send(fileport);
	if (!IP_VALID(sendport)) {
		panic("Couldn't allocate send right for fileport!\n");
	}

out:
	return fileport;
}