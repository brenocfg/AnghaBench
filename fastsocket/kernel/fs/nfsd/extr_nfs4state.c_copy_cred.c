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
struct svc_cred {int /*<<< orphan*/  cr_group_info; int /*<<< orphan*/  cr_gid; int /*<<< orphan*/  cr_uid; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_group_info (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void copy_cred(struct svc_cred *target, struct svc_cred *source)
{
	target->cr_uid = source->cr_uid;
	target->cr_gid = source->cr_gid;
	target->cr_group_info = source->cr_group_info;
	get_group_info(target->cr_group_info);
}