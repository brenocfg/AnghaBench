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
struct shmid_kernel {int /*<<< orphan*/  shm_perm; } ;

/* Variables and functions */
#define  IPC_INFO 135 
#define  IPC_RMID 134 
#define  IPC_SET 133 
#define  IPC_STAT 132 
#define  SHM_INFO 131 
#define  SHM_LOCK 130 
#define  SHM_STAT 129 
#define  SHM_UNLOCK 128 
 int SHM__ASSOCIATE ; 
 int SHM__DESTROY ; 
 int SHM__GETATTR ; 
 int SHM__LOCK ; 
 int SHM__SETATTR ; 
 int /*<<< orphan*/  SYSTEM__IPC_INFO ; 
 int /*<<< orphan*/  current ; 
 int ipc_has_perm (int /*<<< orphan*/ *,int) ; 
 int task_has_system (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int selinux_shm_shmctl(struct shmid_kernel *shp, int cmd)
{
	int perms;
	int err;

	switch (cmd) {
	case IPC_INFO:
	case SHM_INFO:
		/* No specific object, just general system-wide information. */
		return task_has_system(current, SYSTEM__IPC_INFO);
	case IPC_STAT:
	case SHM_STAT:
		perms = SHM__GETATTR | SHM__ASSOCIATE;
		break;
	case IPC_SET:
		perms = SHM__SETATTR;
		break;
	case SHM_LOCK:
	case SHM_UNLOCK:
		perms = SHM__LOCK;
		break;
	case IPC_RMID:
		perms = SHM__DESTROY;
		break;
	default:
		return 0;
	}

	err = ipc_has_perm(&shp->shm_perm, perms);
	return err;
}