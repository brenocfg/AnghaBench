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
typedef  int acl_tag_t ;
typedef  int /*<<< orphan*/ * acl_t ;
typedef  int /*<<< orphan*/  acl_permset_t ;
typedef  int /*<<< orphan*/  acl_flagset_t ;
typedef  scalar_t__ acl_entry_type_t ;
typedef  int /*<<< orphan*/  acl_entry_t ;

/* Variables and functions */
 int ACL_BRAND_NFS4 ; 
#define  ACL_EVERYONE 134 
 int ACL_FIRST_ENTRY ; 
#define  ACL_GROUP 133 
#define  ACL_GROUP_OBJ 132 
#define  ACL_MASK 131 
 int ACL_NEXT_ENTRY ; 
#define  ACL_OTHER 130 
#define  ACL_USER 129 
#define  ACL_USER_OBJ 128 
 int acl_copy_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int acl_create_entry (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int acl_create_entry_np (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * acl_dup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acl_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acl_get_brand_np (int /*<<< orphan*/ *,int*) ; 
 int acl_get_entry (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 scalar_t__ acl_get_entry_type_np (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  acl_get_flagset_np (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int acl_get_permset (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int acl_get_tag_type (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  acl_set_entry_type_np (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  acl_set_flagset_np (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int acl_set_permset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brand_name (int) ; 
 scalar_t__ branding_mismatch (int,int) ; 
 int /*<<< orphan*/  err (int,char*,char const*) ; 
 int /*<<< orphan*/  errx (int,char*,char const*,int) ; 
 int have_mask ; 
 int merge_user_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  warn (char*,char const*) ; 
 int /*<<< orphan*/  warnx (char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
merge_acl(acl_t acl, acl_t *prev_acl, const char *filename)
{
	acl_entry_t entry, entry_new;
	acl_permset_t permset;
	acl_t acl_new;
	acl_tag_t tag, tag_new;
	acl_entry_type_t entry_type, entry_type_new;
	acl_flagset_t flagset;
	int entry_id, entry_id_new, have_entry, had_entry, entry_number = 0;
	int acl_brand, prev_acl_brand;

	acl_get_brand_np(acl, &acl_brand);
	acl_get_brand_np(*prev_acl, &prev_acl_brand);

	if (branding_mismatch(acl_brand, prev_acl_brand)) {
		warnx("%s: branding mismatch; existing ACL is %s, "
		    "entry to be merged is %s", filename,
		    brand_name(prev_acl_brand), brand_name(acl_brand));
		return (-1);
	}

	acl_new = acl_dup(*prev_acl);
	if (acl_new == NULL)
		err(1, "%s: acl_dup() failed", filename);

	entry_id = ACL_FIRST_ENTRY;

	while (acl_get_entry(acl, entry_id, &entry) == 1) {
		entry_id = ACL_NEXT_ENTRY;
		have_entry = 0;
		had_entry = 0;

		/* keep track of existing ACL_MASK entries */
		if (acl_get_tag_type(entry, &tag) == -1)
			err(1, "%s: acl_get_tag_type() failed - "
			    "invalid ACL entry", filename);
		if (tag == ACL_MASK)
			have_mask = true;

		/* check against the existing ACL entries */
		entry_id_new = ACL_FIRST_ENTRY;
		while (acl_get_entry(acl_new, entry_id_new, &entry_new) == 1) {
			entry_id_new = ACL_NEXT_ENTRY;

			if (acl_get_tag_type(entry, &tag) == -1)
				err(1, "%s: acl_get_tag_type() failed",
				    filename);
			if (acl_get_tag_type(entry_new, &tag_new) == -1)
				err(1, "%s: acl_get_tag_type() failed",
				    filename);
			if (tag != tag_new)
				continue;

			/*
			 * For NFSv4, in addition to "tag" and "id" we also
			 * compare "entry_type".
			 */
			if (acl_brand == ACL_BRAND_NFS4) {
				if (acl_get_entry_type_np(entry, &entry_type))
					err(1, "%s: acl_get_entry_type_np() "
					    "failed", filename);
				if (acl_get_entry_type_np(entry_new, &entry_type_new))
					err(1, "%s: acl_get_entry_type_np() "
					    "failed", filename);
				if (entry_type != entry_type_new)
					continue;
			}
		
			switch(tag) {
			case ACL_USER:
			case ACL_GROUP:
				have_entry = merge_user_group(&entry,
				    &entry_new, acl_brand);
				if (have_entry == 0)
					break;
				/* FALLTHROUGH */
			case ACL_USER_OBJ:
			case ACL_GROUP_OBJ:
			case ACL_OTHER:
			case ACL_MASK:
			case ACL_EVERYONE:
				if (acl_get_permset(entry, &permset) == -1)
					err(1, "%s: acl_get_permset() failed",
					    filename);
				if (acl_set_permset(entry_new, permset) == -1)
					err(1, "%s: acl_set_permset() failed",
					    filename);

				if (acl_brand == ACL_BRAND_NFS4) {
					if (acl_get_entry_type_np(entry, &entry_type))
						err(1, "%s: acl_get_entry_type_np() failed",
						    filename);
					if (acl_set_entry_type_np(entry_new, entry_type))
						err(1, "%s: acl_set_entry_type_np() failed",
						    filename);
					if (acl_get_flagset_np(entry, &flagset))
						err(1, "%s: acl_get_flagset_np() failed",
						    filename);
					if (acl_set_flagset_np(entry_new, flagset))
						err(1, "%s: acl_set_flagset_np() failed",
						    filename);
				}
				had_entry = have_entry = 1;
				break;
			default:
				/* should never be here */
				errx(1, "%s: invalid tag type: %i", filename, tag);
				break;
			}
		}

		/* if this entry has not been found, it must be new */
		if (had_entry == 0) {

			/*
			 * NFSv4 ACL entries must be prepended to the ACL.
			 * Appending them at the end makes no sense, since
			 * in most cases they wouldn't even get evaluated.
			 */
			if (acl_brand == ACL_BRAND_NFS4) {
				if (acl_create_entry_np(&acl_new, &entry_new, entry_number) == -1) {
					warn("%s: acl_create_entry_np() failed", filename); 
					acl_free(acl_new);
					return (-1);
				}
				/*
				 * Without this increment, adding several
				 * entries at once, for example
				 * "setfacl -m user:1:r:allow,user:2:r:allow",
				 * would make them appear in reverse order.
				 */
				entry_number++;
			} else {
				if (acl_create_entry(&acl_new, &entry_new) == -1) {
					warn("%s: acl_create_entry() failed", filename); 
					acl_free(acl_new);
					return (-1);
				}
			}
			if (acl_copy_entry(entry_new, entry) == -1)
				err(1, "%s: acl_copy_entry() failed", filename);
		}
	}

	acl_free(*prev_acl);
	*prev_acl = acl_new;

	return (0);
}