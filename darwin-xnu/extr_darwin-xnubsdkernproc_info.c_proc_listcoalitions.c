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
typedef  int /*<<< orphan*/  user_addr_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int ENOTSUP ; 

int proc_listcoalitions(int flavor, int type, user_addr_t buffer,
			uint32_t buffersize, int32_t *retval)
{
#if CONFIG_COALITIONS
	int error = ENOTSUP;
	int coal_type;
	uint32_t elem_size;
	void *coalinfo = NULL;
	uint32_t k_buffersize = 0, copyout_sz = 0;
	int ncoals = 0, ncoals_ = 0;

	/* struct procinfo_coalinfo; */

	switch (flavor) {
	case LISTCOALITIONS_ALL_COALS:
		elem_size = LISTCOALITIONS_ALL_COALS_SIZE;
		coal_type = -1;
		break;
	case LISTCOALITIONS_SINGLE_TYPE:
		elem_size = LISTCOALITIONS_SINGLE_TYPE_SIZE;
		coal_type = type;
		break;
	default:
		return EINVAL;
	}

	/* find the total number of coalitions */
	ncoals = coalitions_get_list(coal_type, NULL, 0);

	if (ncoals == 0 || buffer == 0 || buffersize == 0) {
		/*
		 * user just wants buffer size
		 * or there are no coalitions
		 */
		error = 0;
		*retval = (int)(ncoals * elem_size);
		goto out;
	}

	k_buffersize = ncoals * elem_size;
	coalinfo = kalloc((vm_size_t)k_buffersize);
	if (!coalinfo) {
		error = ENOMEM;
		goto out;
	}
	bzero(coalinfo, k_buffersize);

	switch (flavor) {
	case LISTCOALITIONS_ALL_COALS:
	case LISTCOALITIONS_SINGLE_TYPE:
		ncoals_ = coalitions_get_list(coal_type, coalinfo, ncoals);
		break;
	default:
		panic("memory corruption?!");
	}

	if (ncoals_ == 0) {
		/* all the coalitions disappeared... weird but valid */
		error = 0;
		*retval = 0;
		goto out;
	}

	/*
	 * Some coalitions may have disappeared between our initial check,
	 * and the the actual list acquisition.
	 * Only copy out what we really need.
	 */
	copyout_sz = k_buffersize;
	if (ncoals_ < ncoals)
		copyout_sz = ncoals_ * elem_size;

	/*
	 * copy the list up to user space
	 * (we're guaranteed to have a non-null pointer/size here)
	 */
	error = copyout(coalinfo, buffer,
			copyout_sz < buffersize ? copyout_sz : buffersize);

	if (error == 0)
		*retval = (int)copyout_sz;

out:
	if (coalinfo)
		kfree(coalinfo, k_buffersize);

	return error;
#else
	/* no coalition support */
	(void)flavor;
	(void)type;
	(void)buffer;
	(void)buffersize;
	(void)retval;
	return ENOTSUP;
#endif
}