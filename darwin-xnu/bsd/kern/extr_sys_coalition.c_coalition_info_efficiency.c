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
typedef  int /*<<< orphan*/  user_size_t ;
typedef  int /*<<< orphan*/  user_addr_t ;
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  flags ;
typedef  int /*<<< orphan*/  coalition_t ;

/* Variables and functions */
 int COALITION_EFFICIENCY_VALID_FLAGS ; 
 int COALITION_FLAGS_EFFICIENT ; 
 scalar_t__ COALITION_TYPE_JETSAM ; 
 int EINVAL ; 
 int /*<<< orphan*/  MIN (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  coalition_set_efficient (int /*<<< orphan*/ ) ; 
 scalar_t__ coalition_type (int /*<<< orphan*/ ) ; 
 int copyin (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
coalition_info_efficiency(coalition_t coal, user_addr_t buffer, user_size_t bufsize)
{
	int error = 0;
	if (coalition_type(coal) != COALITION_TYPE_JETSAM)
		return EINVAL;
	uint64_t flags = 0;	
	error = copyin(buffer, &flags, MIN(bufsize, sizeof(flags)));
	if (error)
		return error;
	if ((flags & COALITION_EFFICIENCY_VALID_FLAGS) == 0)
		return EINVAL;
	if (flags & COALITION_FLAGS_EFFICIENT) {
	    coalition_set_efficient(coal);
	}
	return error;
}