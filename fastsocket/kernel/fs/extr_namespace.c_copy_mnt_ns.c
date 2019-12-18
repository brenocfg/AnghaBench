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
struct mnt_namespace {int dummy; } ;
struct fs_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned long CLONE_NEWNS ; 
 struct mnt_namespace* dup_mnt_ns (struct mnt_namespace*,struct fs_struct*) ; 
 int /*<<< orphan*/  get_mnt_ns (struct mnt_namespace*) ; 
 int /*<<< orphan*/  put_mnt_ns (struct mnt_namespace*) ; 

struct mnt_namespace *copy_mnt_ns(unsigned long flags, struct mnt_namespace *ns,
		struct fs_struct *new_fs)
{
	struct mnt_namespace *new_ns;

	BUG_ON(!ns);
	get_mnt_ns(ns);

	if (!(flags & CLONE_NEWNS))
		return ns;

	new_ns = dup_mnt_ns(ns, new_fs);

	put_mnt_ns(ns);
	return new_ns;
}