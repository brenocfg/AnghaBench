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
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int dsl_dataset_user_release (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fnvlist_add_boolean (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  fnvlist_add_nvlist (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fnvlist_alloc () ; 
 int /*<<< orphan*/  fnvlist_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
user_release_one(const char *snapname, const char *holdname)
{
	nvlist_t *snaps, *holds;
	int error;

	snaps = fnvlist_alloc();
	holds = fnvlist_alloc();
	fnvlist_add_boolean(holds, holdname);
	fnvlist_add_nvlist(snaps, snapname, holds);
	fnvlist_free(holds);
	error = dsl_dataset_user_release(snaps, NULL);
	fnvlist_free(snaps);
	return (error);
}