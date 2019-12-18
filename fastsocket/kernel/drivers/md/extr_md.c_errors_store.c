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
struct md_rdev {int /*<<< orphan*/  corrected_errors; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,unsigned long) ; 
 unsigned long simple_strtoul (char const*,char**,int) ; 

__attribute__((used)) static ssize_t
errors_store(struct md_rdev *rdev, const char *buf, size_t len)
{
	char *e;
	unsigned long n = simple_strtoul(buf, &e, 10);
	if (*buf && (*e == 0 || *e == '\n')) {
		atomic_set(&rdev->corrected_errors, n);
		return len;
	}
	return -EINVAL;
}