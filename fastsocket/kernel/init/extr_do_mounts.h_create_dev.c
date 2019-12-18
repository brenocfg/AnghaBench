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
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 int S_IFBLK ; 
 int /*<<< orphan*/  new_encode_dev (int /*<<< orphan*/ ) ; 
 int sys_mknod (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sys_unlink (char*) ; 

__attribute__((used)) static inline int create_dev(char *name, dev_t dev)
{
	sys_unlink(name);
	return sys_mknod(name, S_IFBLK|0600, new_encode_dev(dev));
}