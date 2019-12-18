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
struct nfs4_stateid {scalar_t__ st_stateowner; int /*<<< orphan*/  st_file; } ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  fl_owner_t ;

/* Variables and functions */
 struct file* find_any_file (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_generic_stateid (struct nfs4_stateid*) ; 
 int /*<<< orphan*/  locks_remove_posix (struct file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unhash_generic_stateid (struct nfs4_stateid*) ; 

__attribute__((used)) static void release_lock_stateid(struct nfs4_stateid *stp)
{
	struct file *file;

	unhash_generic_stateid(stp);
	file = find_any_file(stp->st_file);
	if (file)
		locks_remove_posix(file, (fl_owner_t)stp->st_stateowner);
	free_generic_stateid(stp);
}