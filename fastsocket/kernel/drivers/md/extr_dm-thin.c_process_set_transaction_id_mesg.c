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
struct pool {int /*<<< orphan*/  pmd; } ;
typedef  int /*<<< orphan*/  dm_thin_id ;

/* Variables and functions */
 int /*<<< orphan*/  DMWARN (char*,char*,...) ; 
 int EINVAL ; 
 int check_arg_count (unsigned int,int) ; 
 int dm_pool_set_metadata_transaction_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ kstrtoull (char*,int,unsigned long long*) ; 

__attribute__((used)) static int process_set_transaction_id_mesg(unsigned argc, char **argv, struct pool *pool)
{
	dm_thin_id old_id, new_id;
	int r;

	r = check_arg_count(argc, 3);
	if (r)
		return r;

	if (kstrtoull(argv[1], 10, (unsigned long long *)&old_id)) {
		DMWARN("set_transaction_id message: Unrecognised id %s.", argv[1]);
		return -EINVAL;
	}

	if (kstrtoull(argv[2], 10, (unsigned long long *)&new_id)) {
		DMWARN("set_transaction_id message: Unrecognised new id %s.", argv[2]);
		return -EINVAL;
	}

	r = dm_pool_set_metadata_transaction_id(pool->pmd, old_id, new_id);
	if (r) {
		DMWARN("Failed to change transaction id from %s to %s.",
		       argv[1], argv[2]);
		return r;
	}

	return 0;
}