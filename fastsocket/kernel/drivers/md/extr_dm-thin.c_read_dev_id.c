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
typedef  scalar_t__ dm_thin_id ;

/* Variables and functions */
 int /*<<< orphan*/  DMWARN (char*,char*) ; 
 int EINVAL ; 
 scalar_t__ MAX_DEV_ID ; 
 int /*<<< orphan*/  kstrtoull (char*,int,unsigned long long*) ; 

__attribute__((used)) static int read_dev_id(char *arg, dm_thin_id *dev_id, int warning)
{
	if (!kstrtoull(arg, 10, (unsigned long long *)dev_id) &&
	    *dev_id <= MAX_DEV_ID)
		return 0;

	if (warning)
		DMWARN("Message received with invalid device id: %s", arg);

	return -EINVAL;
}