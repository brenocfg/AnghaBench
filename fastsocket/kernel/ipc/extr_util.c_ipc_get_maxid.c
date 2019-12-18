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
struct kern_ipc_perm {int dummy; } ;
struct ipc_ids {int in_use; int /*<<< orphan*/  ipcs_idr; } ;

/* Variables and functions */
 int IPCMNI ; 
 struct kern_ipc_perm* idr_find (int /*<<< orphan*/ *,int) ; 

int ipc_get_maxid(struct ipc_ids *ids)
{
	struct kern_ipc_perm *ipc;
	int max_id = -1;
	int total, id;

	if (ids->in_use == 0)
		return -1;

	if (ids->in_use == IPCMNI)
		return IPCMNI - 1;

	/* Look for the last assigned id */
	total = 0;
	for (id = 0; id < IPCMNI && total < ids->in_use; id++) {
		ipc = idr_find(&ids->ipcs_idr, id);
		if (ipc != NULL) {
			max_id = id;
			total++;
		}
	}
	return max_id;
}