#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_5__ {int /*<<< orphan*/  key; struct ipc_security_struct* security; } ;
struct shmid_kernel {TYPE_2__ shm_perm; } ;
struct ipc_security_struct {int /*<<< orphan*/  sid; } ;
struct TYPE_4__ {int /*<<< orphan*/  ipc_id; } ;
struct common_audit_data {TYPE_1__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMMON_AUDIT_DATA_INIT (struct common_audit_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPC ; 
 int /*<<< orphan*/  SECCLASS_SHM ; 
 int /*<<< orphan*/  SHM__CREATE ; 
 int avc_has_perm (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct common_audit_data*) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  current_sid () ; 
 int ipc_alloc_security (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipc_free_security (TYPE_2__*) ; 

__attribute__((used)) static int selinux_shm_alloc_security(struct shmid_kernel *shp)
{
	struct ipc_security_struct *isec;
	struct common_audit_data ad;
	u32 sid = current_sid();
	int rc;

	rc = ipc_alloc_security(current, &shp->shm_perm, SECCLASS_SHM);
	if (rc)
		return rc;

	isec = shp->shm_perm.security;

	COMMON_AUDIT_DATA_INIT(&ad, IPC);
	ad.u.ipc_id = shp->shm_perm.key;

	rc = avc_has_perm(sid, isec->sid, SECCLASS_SHM,
			  SHM__CREATE, &ad);
	if (rc) {
		ipc_free_security(&shp->shm_perm);
		return rc;
	}
	return 0;
}