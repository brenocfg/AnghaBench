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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  u_longlong_t ;

/* Variables and functions */
 scalar_t__ FUID_INDEX (scalar_t__) ; 
 scalar_t__ FUID_RID (scalar_t__) ; 
 int /*<<< orphan*/  idx_tree ; 
 int /*<<< orphan*/  printf (char*,char const*,int /*<<< orphan*/ ,...) ; 
 char* zfs_fuid_idx_domain (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void
print_idstr(uint64_t id, const char *id_type)
{
	if (FUID_INDEX(id)) {
		char *domain;

		domain = zfs_fuid_idx_domain(&idx_tree, FUID_INDEX(id));
		(void) printf("\t%s     %llx [%s-%d]\n", id_type,
		    (u_longlong_t)id, domain, (int)FUID_RID(id));
	} else {
		(void) printf("\t%s     %llu\n", id_type, (u_longlong_t)id);
	}

}