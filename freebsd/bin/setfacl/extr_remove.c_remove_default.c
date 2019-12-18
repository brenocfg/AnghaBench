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
typedef  int /*<<< orphan*/ * acl_t ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_MAX_ENTRIES ; 
 int /*<<< orphan*/  acl_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * acl_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (int,char*,char const*) ; 

int
remove_default(acl_t *prev_acl, const char *filename)
{

	acl_free(*prev_acl);
	*prev_acl = acl_init(ACL_MAX_ENTRIES);
	if (*prev_acl == NULL)
		err(1, "%s: acl_init() failed", filename);

	return (0);
}