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
struct mddev {int /*<<< orphan*/  recovery; int /*<<< orphan*/  ro; } ;

/* Variables and functions */
 int /*<<< orphan*/  MD_RECOVERY_CHECK ; 
 int /*<<< orphan*/  MD_RECOVERY_FROZEN ; 
 int /*<<< orphan*/  MD_RECOVERY_NEEDED ; 
 int /*<<< orphan*/  MD_RECOVERY_RECOVER ; 
 int /*<<< orphan*/  MD_RECOVERY_REQUESTED ; 
 int /*<<< orphan*/  MD_RECOVERY_RESHAPE ; 
 int /*<<< orphan*/  MD_RECOVERY_RUNNING ; 
 int /*<<< orphan*/  MD_RECOVERY_SYNC ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static const char *decipher_sync_action(struct mddev *mddev)
{
	if (test_bit(MD_RECOVERY_FROZEN, &mddev->recovery))
		return "frozen";

	if (test_bit(MD_RECOVERY_RUNNING, &mddev->recovery) ||
	    (!mddev->ro && test_bit(MD_RECOVERY_NEEDED, &mddev->recovery))) {
		if (test_bit(MD_RECOVERY_RESHAPE, &mddev->recovery))
			return "reshape";

		if (test_bit(MD_RECOVERY_SYNC, &mddev->recovery)) {
			if (!test_bit(MD_RECOVERY_REQUESTED, &mddev->recovery))
				return "resync";
			else if (test_bit(MD_RECOVERY_CHECK, &mddev->recovery))
				return "check";
			return "repair";
		}

		if (test_bit(MD_RECOVERY_RECOVER, &mddev->recovery))
			return "recover";
	}

	return "idle";
}