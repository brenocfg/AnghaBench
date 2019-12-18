#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct uuid_command {int cmdsize; int /*<<< orphan*/ * uuid; } ;
typedef  int /*<<< orphan*/  load_return_t ;
struct TYPE_3__ {int /*<<< orphan*/ * uuid; } ;
typedef  TYPE_1__ load_result_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOAD_BADMACHO ; 
 int /*<<< orphan*/  LOAD_SUCCESS ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static
load_return_t
load_uuid(
	struct uuid_command	*uulp,
	char			*command_end,
	load_result_t		*result
)
{
		/*
		 * We need to check the following for this command:
		 * - The command size should be atleast the size of struct uuid_command
		 * - The UUID part of the command should be completely within the mach-o header
		 */

		if ((uulp->cmdsize < sizeof(struct uuid_command)) ||
		    (((char *)uulp + sizeof(struct uuid_command)) > command_end)) {
			return (LOAD_BADMACHO);
		}
		
		memcpy(&result->uuid[0], &uulp->uuid[0], sizeof(result->uuid));
		return (LOAD_SUCCESS);
}