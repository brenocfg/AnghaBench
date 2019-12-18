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
struct pshmobj {int pshm_flags; struct pshmobj* pshmo_next; int /*<<< orphan*/  pshmo_memobject; struct pshmobj* pshm_memobjects; int /*<<< orphan*/  pshm_usecount; } ;
struct pshminfo {int pshm_flags; struct pshminfo* pshmo_next; int /*<<< orphan*/  pshmo_memobject; struct pshminfo* pshm_memobjects; int /*<<< orphan*/  pshm_usecount; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FREE (struct pshmobj*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_SHM ; 
 int PSHM_ALLOCATED ; 
 int PSHM_REMOVED ; 
 int /*<<< orphan*/  PSHM_SUBSYS_LOCK () ; 
 int /*<<< orphan*/  PSHM_SUBSYS_UNLOCK () ; 
 int /*<<< orphan*/  kprintf (char*) ; 
 int /*<<< orphan*/  mac_posixshm_label_destroy (struct pshmobj*) ; 
 int /*<<< orphan*/  mach_memory_entry_port_release (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pshm_close(struct pshminfo *pinfo, int dropref)
{
	int error = 0;
	struct pshmobj *pshmobj, *pshmobj_next;

	/*
	 * If we are dropping the reference we took on the cache object, don't
	 * enforce the allocation requirement.
	 */
	if ( !dropref && ((pinfo->pshm_flags & PSHM_ALLOCATED) != PSHM_ALLOCATED)) {
		return(EINVAL);
	}
#if DIAGNOSTIC
	if(!pinfo->pshm_usecount) {
		kprintf("negative usecount in pshm_close\n");
	}
#endif /* DIAGNOSTIC */
	pinfo->pshm_usecount--; /* release this fd's reference */

 	if ((pinfo->pshm_flags & PSHM_REMOVED) && !pinfo->pshm_usecount) {
#if CONFIG_MACF
		mac_posixshm_label_destroy(pinfo);
#endif
		PSHM_SUBSYS_UNLOCK();
		/*
		 * If this is the last reference going away on the object,
		 * then we need to destroy the backing object.
		 */
		for (pshmobj = pinfo->pshm_memobjects;
		     pshmobj != NULL;
		     pshmobj = pshmobj_next) {
			mach_memory_entry_port_release(pshmobj->pshmo_memobject);
			pshmobj_next = pshmobj->pshmo_next;
			FREE(pshmobj, M_SHM);
		}
		PSHM_SUBSYS_LOCK();
		FREE(pinfo,M_SHM);
	}
	return (error);
}