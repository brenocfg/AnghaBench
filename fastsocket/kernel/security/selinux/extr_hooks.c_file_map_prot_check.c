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
struct file {int dummy; } ;
struct cred {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FILE__EXECUTE ; 
 int /*<<< orphan*/  FILE__READ ; 
 int /*<<< orphan*/  FILE__WRITE ; 
 int /*<<< orphan*/  PROCESS__EXECMEM ; 
 unsigned long PROT_EXEC ; 
 unsigned long PROT_WRITE ; 
 int cred_has_perm (struct cred const*,struct cred const*,int /*<<< orphan*/ ) ; 
 struct cred* current_cred () ; 
 int file_has_perm (struct cred const*,struct file*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int file_map_prot_check(struct file *file, unsigned long prot, int shared)
{
	const struct cred *cred = current_cred();
	int rc = 0;

#ifndef CONFIG_PPC32
	if ((prot & PROT_EXEC) && (!file || (!shared && (prot & PROT_WRITE)))) {
		/*
		 * We are making executable an anonymous mapping or a
		 * private file mapping that will also be writable.
		 * This has an additional check.
		 */
		rc = cred_has_perm(cred, cred, PROCESS__EXECMEM);
		if (rc)
			goto error;
	}
#endif

	if (file) {
		/* read access is always possible with a mapping */
		u32 av = FILE__READ;

		/* write access only matters if the mapping is shared */
		if (shared && (prot & PROT_WRITE))
			av |= FILE__WRITE;

		if (prot & PROT_EXEC)
			av |= FILE__EXECUTE;

		return file_has_perm(cred, file, av);
	}

error:
	return rc;
}