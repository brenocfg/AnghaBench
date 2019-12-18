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
struct mddev {unsigned long long suspend_hi; TYPE_1__* pers; } ;
typedef  size_t ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* quiesce ) (struct mddev*,int) ;} ;

/* Variables and functions */
 size_t EINVAL ; 
 unsigned long long simple_strtoull (char const*,char**,int) ; 
 int /*<<< orphan*/  stub1 (struct mddev*,int) ; 
 int /*<<< orphan*/  stub2 (struct mddev*,int) ; 
 int /*<<< orphan*/  stub3 (struct mddev*,int) ; 

__attribute__((used)) static ssize_t
suspend_hi_store(struct mddev *mddev, const char *buf, size_t len)
{
	char *e;
	unsigned long long new = simple_strtoull(buf, &e, 10);
	unsigned long long old = mddev->suspend_hi;

	if (mddev->pers == NULL ||
	    mddev->pers->quiesce == NULL)
		return -EINVAL;
	if (buf == e || (*e && *e != '\n'))
		return -EINVAL;

	mddev->suspend_hi = new;
	if (new <= old)
		/* Shrinking suspended region */
		mddev->pers->quiesce(mddev, 2);
	else {
		/* Expanding suspended region - need to wait */
		mddev->pers->quiesce(mddev, 1);
		mddev->pers->quiesce(mddev, 0);
	}
	return len;
}