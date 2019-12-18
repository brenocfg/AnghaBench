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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct proc_dir_entry {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int selinux_proc_get_sid(struct proc_dir_entry *de,
				u16 tclass,
				u32 *sid)
{
	return -EINVAL;
}