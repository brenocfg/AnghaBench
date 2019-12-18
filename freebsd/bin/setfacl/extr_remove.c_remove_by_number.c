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
typedef  scalar_t__ uint ;
typedef  scalar_t__ acl_tag_t ;
typedef  int /*<<< orphan*/ * acl_t ;
typedef  int /*<<< orphan*/  acl_entry_t ;

/* Variables and functions */
 int ACL_FIRST_ENTRY ; 
 scalar_t__ ACL_MASK ; 
 int ACL_NEXT_ENTRY ; 
 scalar_t__ ACL_UNDEFINED_TAG ; 
 int acl_delete_entry_np (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ * acl_dup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acl_free (int /*<<< orphan*/ *) ; 
 int acl_get_entry (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int acl_get_tag_type (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  err (int,char*,char const*) ; 
 int have_mask ; 
 int /*<<< orphan*/  warn (char*,char const*) ; 

int
remove_by_number(uint entry_number, acl_t *prev_acl, const char *filename)
{
	acl_entry_t	entry;
	acl_t		acl_new;
	acl_tag_t	tag;
	int		carried_error, entry_id;
	uint		i;

	carried_error = 0;

	acl_new = acl_dup(*prev_acl);
	if (acl_new == NULL)
		err(1, "%s: acl_dup() failed", filename);

	tag = ACL_UNDEFINED_TAG;

	/*
	 * Find out whether we're removing the mask entry,
	 * to behave the same as the routine above.
	 *
	 * XXX: Is this loop actually needed?
	 */
	entry_id = ACL_FIRST_ENTRY;
	i = 0;
	while (acl_get_entry(acl_new, entry_id, &entry) == 1) {
		entry_id = ACL_NEXT_ENTRY;
		if (i != entry_number)
			continue;
		if (acl_get_tag_type(entry, &tag) == -1)
			err(1, "%s: acl_get_tag_type() failed", filename);
		if (tag == ACL_MASK)
			have_mask = true;
	}

	if (acl_delete_entry_np(acl_new, entry_number) == -1) {
		carried_error++;
		warn("%s: acl_delete_entry_np() failed", filename);
	}

	acl_free(*prev_acl);
	*prev_acl = acl_new;

	if (carried_error)
		return (-1);

	return (0);
}