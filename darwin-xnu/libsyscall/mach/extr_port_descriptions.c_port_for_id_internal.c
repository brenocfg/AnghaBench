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

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ strcmp (char const*,char const*) ; 

__attribute__((used)) static int
port_for_id_internal(const char *id, const char **ids, int nids)
{
	if (!id) {
		errno = EINVAL;
		return -1;
	}

	for (int i = 0; i < nids; i++) {
		if (ids[i] && strcmp(ids[i], id) == 0) {
			return i;
		}
	}

	errno = ENOENT;
	return -1;
}