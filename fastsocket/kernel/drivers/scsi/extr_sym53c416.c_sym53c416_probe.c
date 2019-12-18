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
 int /*<<< orphan*/  ID ; 
 int /*<<< orphan*/  IO_RANGE ; 
 int* probeaddrs ; 
 int /*<<< orphan*/  release_region (int,int /*<<< orphan*/ ) ; 
 scalar_t__ request_region (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sym53c416_setup (int /*<<< orphan*/ *,int*) ; 
 scalar_t__ sym53c416_test (int) ; 

__attribute__((used)) static void sym53c416_probe(void)
{
	int *base = probeaddrs;
	int ints[2];

	ints[0] = 1;
	for(; *base; base++) {
		if (request_region(*base, IO_RANGE, ID)) {
			if (sym53c416_test(*base)) {
				ints[1] = *base;
				sym53c416_setup(NULL, ints);
			}
			release_region(*base, IO_RANGE);
		}
	}
}