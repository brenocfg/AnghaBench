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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;
typedef  scalar_t__ kern_return_t ;
typedef  int /*<<< orphan*/  coalition_t ;
typedef  int /*<<< orphan*/  cid ;
typedef  int boolean_t ;

/* Variables and functions */
 int COALITION_CREATE_FLAGS_GET_ROLE (int) ; 
 int COALITION_CREATE_FLAGS_GET_TYPE (int) ; 
 int COALITION_CREATE_FLAGS_MASK ; 
 int COALITION_CREATE_FLAGS_PRIVILEGED ; 
 int COALITION_TYPE_MAX ; 
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  coal_dbg (char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ coalition_create_internal (int,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  coalition_id (int /*<<< orphan*/ ) ; 
 int copyout (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static
int
coalition_create_syscall(user_addr_t cidp, uint32_t flags)
{
	int error = 0;
	kern_return_t kr;
	uint64_t cid;
	coalition_t coal;
	int type = COALITION_CREATE_FLAGS_GET_TYPE(flags);
	int role = COALITION_CREATE_FLAGS_GET_ROLE(flags);
	boolean_t privileged = !!(flags & COALITION_CREATE_FLAGS_PRIVILEGED);

	if ((flags & (~COALITION_CREATE_FLAGS_MASK)) != 0)
		return EINVAL;
	if (type < 0 || type > COALITION_TYPE_MAX)
		return EINVAL;

	kr = coalition_create_internal(type, role, privileged, &coal);
	if (kr != KERN_SUCCESS) {
		/* for now, the only kr is KERN_RESOURCE_SHORTAGE */
		error = ENOMEM;
		goto out;
	}

	cid = coalition_id(coal);

	coal_dbg("(addr, %u) -> %llu", flags, cid);
	error = copyout(&cid, cidp, sizeof(cid));
out:
	return error;
}