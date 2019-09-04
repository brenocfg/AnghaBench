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
typedef  int /*<<< orphan*/  uint64_t ;
struct mach_generate_activity_id_args {scalar_t__ count; int /*<<< orphan*/  activity_id; } ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  int /*<<< orphan*/  activity_id ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 scalar_t__ MACH_ACTIVITY_ID_COUNT_MAX ; 
 int /*<<< orphan*/  copyout (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  generate_activity_id (scalar_t__) ; 

kern_return_t
mach_generate_activity_id(
	struct mach_generate_activity_id_args *args)
{
	uint64_t activity_id;
	kern_return_t kr = KERN_SUCCESS;

	if (args->count <= 0 || args->count > MACH_ACTIVITY_ID_COUNT_MAX) {
		return KERN_INVALID_ARGUMENT;
	}

	activity_id = generate_activity_id(args->count);
	kr = copyout(&activity_id, args->activity_id, sizeof (activity_id));

	return (kr);
}