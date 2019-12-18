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
typedef  scalar_t__ acl_tag_t ;
typedef  int /*<<< orphan*/ * acl_t ;
typedef  int /*<<< orphan*/ * acl_entry_t ;

/* Variables and functions */
 int ACL_FIRST_ENTRY ; 
 scalar_t__ ACL_MASK ; 
 int ACL_NEXT_ENTRY ; 
 scalar_t__ acl_calc_mask (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * acl_dup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acl_free (int /*<<< orphan*/ *) ; 
 int acl_get_entry (int /*<<< orphan*/ *,int,int /*<<< orphan*/ **) ; 
 int acl_get_tag_type (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  err (int,char*,char const*) ; 
 scalar_t__ have_mask ; 
 int /*<<< orphan*/  n_flag ; 
 int /*<<< orphan*/  warn (char*,char const*) ; 
 int /*<<< orphan*/  warnx (char*,char const*) ; 

int
set_acl_mask(acl_t *prev_acl, const char *filename)
{
	acl_entry_t entry;
	acl_t acl;
	acl_tag_t tag;
	int entry_id;

	entry = NULL;

	/*
	 * ... if a mask entry is specified, then the permissions of the mask
	 * entry in the resulting ACL shall be set to the permissions in the
	 * specified ACL mask entry.
	 */
	if (have_mask)
		return (0);

	acl = acl_dup(*prev_acl);
	if (acl == NULL)
		err(1, "%s: acl_dup() failed", filename);

	if (!n_flag) {
		/*
		 * If no mask entry is specified and the -n option is not
		 * specified, then the permissions of the resulting ACL mask
		 * entry shall be set to the union of the permissions
		 * associated with all entries which belong to the file group
		 * class in the resulting ACL
		 */
		if (acl_calc_mask(&acl)) {
			warn("%s: acl_calc_mask() failed", filename);
			acl_free(acl);
			return (-1);
		}
	} else {
		/*
		 * If no mask entry is specified and the -n option is
		 * specified, then the permissions of the resulting ACL
		 * mask entry shall remain unchanged ...
		 */

		entry_id = ACL_FIRST_ENTRY;

		while (acl_get_entry(acl, entry_id, &entry) == 1) {
			entry_id = ACL_NEXT_ENTRY;
			if (acl_get_tag_type(entry, &tag) == -1)
				err(1, "%s: acl_get_tag_type() failed",
				    filename);

			if (tag == ACL_MASK) {
				acl_free(acl);
				return (0);
			}
		}

		/*
		 * If no mask entry is specified, the -n option is specified,
		 * and no ACL mask entry exists in the ACL associated with the
		 * file, then write an error message to standard error and
		 * continue with the next file.
		 */
		warnx("%s: warning: no mask entry", filename);
		acl_free(acl);
		return (0);
	}

	acl_free(*prev_acl);
	*prev_acl = acl_dup(acl);
	acl_free(acl);

	return (0);
}