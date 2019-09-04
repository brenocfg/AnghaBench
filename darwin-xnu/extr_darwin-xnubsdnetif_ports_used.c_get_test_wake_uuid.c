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
typedef  int /*<<< orphan*/ * uuid_t ;

/* Variables and functions */
 scalar_t__ __improbable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_wakeuuid ; 
 int /*<<< orphan*/  use_test_wakeuuid ; 
 int /*<<< orphan*/  uuid_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uuid_is_null (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
get_test_wake_uuid(uuid_t wakeuuid)
{
	if (__improbable(use_test_wakeuuid)) {
		if (!uuid_is_null(test_wakeuuid)) {
			if (wakeuuid != NULL) {
				uuid_copy(wakeuuid, test_wakeuuid);
			}
			return (true);
		} else {
			return (false);
		}
	} else {
		return (false);
	}
}