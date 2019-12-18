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
struct inode {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTK (int /*<<< orphan*/ ,char*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  EPRINTK_LIMIT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ERR ; 
 int /*<<< orphan*/  INFO ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  cpus_clear (int /*<<< orphan*/ ) ; 
 scalar_t__ fastsocket_spawn_cpu ; 
 int /*<<< orphan*/  fastsocket_spawn_cpuset ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fastsocket_open(struct inode *inode, struct file *filp)
{
	if (!try_module_get(THIS_MODULE)) {
		EPRINTK_LIMIT(ERR, "Add reference to fastsocket module failed\n");
		return -EINVAL;
	}

	DPRINTK(INFO, "Hold module reference\n");

	cpus_clear(fastsocket_spawn_cpuset);
	fastsocket_spawn_cpu = 0;

	return 0;
}