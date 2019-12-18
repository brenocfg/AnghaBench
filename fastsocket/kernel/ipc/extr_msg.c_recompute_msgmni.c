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
struct sysinfo {unsigned long totalram; unsigned long totalhigh; unsigned long mem_unit; } ;
struct ipc_namespace {unsigned long msg_ctlmni; } ;

/* Variables and functions */
 int IPCMNI ; 
 unsigned long MSGMNB ; 
 unsigned long MSGMNI ; 
 unsigned long MSG_MEM_SCALE ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nr_ipc_ns ; 
 int /*<<< orphan*/  si_meminfo (struct sysinfo*) ; 

void recompute_msgmni(struct ipc_namespace *ns)
{
	struct sysinfo i;
	unsigned long allowed;
	int nb_ns;

	si_meminfo(&i);
	allowed = (((i.totalram - i.totalhigh) / MSG_MEM_SCALE) * i.mem_unit)
		/ MSGMNB;
	nb_ns = atomic_read(&nr_ipc_ns);
	allowed /= nb_ns;

	if (allowed < MSGMNI) {
		ns->msg_ctlmni = MSGMNI;
		return;
	}

	if (allowed > IPCMNI / nb_ns) {
		ns->msg_ctlmni = IPCMNI / nb_ns;
		return;
	}

	ns->msg_ctlmni = allowed;
}