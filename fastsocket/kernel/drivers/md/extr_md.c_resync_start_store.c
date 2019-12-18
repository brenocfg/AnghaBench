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
struct mddev {unsigned long long recovery_cp; int /*<<< orphan*/  flags; scalar_t__ pers; int /*<<< orphan*/  recovery; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EBUSY ; 
 size_t EINVAL ; 
 int /*<<< orphan*/  MD_CHANGE_CLEAN ; 
 int /*<<< orphan*/  MD_RECOVERY_FROZEN ; 
 unsigned long long MaxSector ; 
 scalar_t__ cmd_match (char const*,char*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 unsigned long long simple_strtoull (char const*,char**,int) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t
resync_start_store(struct mddev *mddev, const char *buf, size_t len)
{
	char *e;
	unsigned long long n = simple_strtoull(buf, &e, 10);

	if (mddev->pers && !test_bit(MD_RECOVERY_FROZEN, &mddev->recovery))
		return -EBUSY;
	if (cmd_match(buf, "none"))
		n = MaxSector;
	else if (!*buf || (*e && *e != '\n'))
		return -EINVAL;

	mddev->recovery_cp = n;
	if (mddev->pers)
		set_bit(MD_CHANGE_CLEAN, &mddev->flags);
	return len;
}