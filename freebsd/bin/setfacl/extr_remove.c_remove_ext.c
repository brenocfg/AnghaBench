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
 int /*<<< orphan*/  acl_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * acl_strip_np (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  err (int,char*,char const*) ; 
 int /*<<< orphan*/  n_flag ; 

void
remove_ext(acl_t *prev_acl, const char *filename)
{
	acl_t acl_new;

	acl_new = acl_strip_np(*prev_acl, !n_flag);
	if (acl_new == NULL)
		err(1, "%s: acl_strip_np() failed", filename);

	acl_free(*prev_acl);
	*prev_acl = acl_new;
}