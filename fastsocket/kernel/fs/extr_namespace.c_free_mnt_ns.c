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
struct mnt_namespace {int /*<<< orphan*/  proc_inum; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct mnt_namespace*) ; 
 int /*<<< orphan*/  proc_free_inum (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_mnt_ns(struct mnt_namespace *ns)
{
	proc_free_inum(ns->proc_inum);
	kfree(ns);
}