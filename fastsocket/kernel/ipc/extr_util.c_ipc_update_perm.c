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
struct kern_ipc_perm {int mode; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; } ;
struct ipc64_perm {int mode; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; } ;

/* Variables and functions */
 int S_IRWXUGO ; 

void ipc_update_perm(struct ipc64_perm *in, struct kern_ipc_perm *out)
{
	out->uid = in->uid;
	out->gid = in->gid;
	out->mode = (out->mode & ~S_IRWXUGO)
		| (in->mode & S_IRWXUGO);
}