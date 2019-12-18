#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int signature; int /*<<< orphan*/  name; } ;
struct nvram_partition {TYPE_1__ header; } ;

/* Variables and functions */
 scalar_t__ strncmp (char const* const,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int nvram_can_remove_partition(struct nvram_partition *part,
		const char *name, int sig, const char *const exceptions[])
{
	if (part->header.signature != sig)
		return 0;
	if (name) {
		if (strncmp(name, part->header.name, 12))
			return 0;
	} else if (exceptions) {
		const char *const *except;
		for (except = exceptions; *except; except++) {
			if (!strncmp(*except, part->header.name, 12))
				return 0;
		}
	}
	return 1;
}