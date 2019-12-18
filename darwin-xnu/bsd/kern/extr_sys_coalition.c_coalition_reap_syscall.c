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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int kern_return_t ;
typedef  scalar_t__ coalition_t ;
typedef  int /*<<< orphan*/  cid ;

/* Variables and functions */
 scalar_t__ COALITION_NULL ; 
 int EBUSY ; 
 int EINVAL ; 
 int EIO ; 
 int EPERM ; 
 int ESRCH ; 
#define  KERN_DEFAULT_SET 131 
#define  KERN_FAILURE 130 
#define  KERN_SUCCESS 129 
#define  KERN_TERMINATED 128 
 int /*<<< orphan*/  coal_dbg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ coalition_find_by_id (int /*<<< orphan*/ ) ; 
 int coalition_reap_internal (scalar_t__) ; 
 int /*<<< orphan*/  coalition_release (scalar_t__) ; 
 int copyin (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static
int
coalition_reap_syscall(user_addr_t cidp, uint32_t flags)
{
	kern_return_t kr;
	int error = 0;
	uint64_t cid;
	coalition_t coal;

	if (flags != 0) {
		return EINVAL;
	}

	error = copyin(cidp, &cid, sizeof(cid));
	if (error) {
		return error;
	}

	coal = coalition_find_by_id(cid);
	if (coal == COALITION_NULL) {
		return ESRCH;
	}

	kr = coalition_reap_internal(coal);
	coalition_release(coal);

	switch (kr) {
	case KERN_SUCCESS:
		break;
	case KERN_DEFAULT_SET:
		error = EPERM;
		break;
	case KERN_TERMINATED:
		error = ESRCH;
		break;
	case KERN_FAILURE:
		error = EBUSY;
		break;
	default:
		error = EIO;
		break;
	}

	coal_dbg("(%llu, %u) -> %d", cid, flags, error);

	return error;
}