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
typedef  int u32 ;
struct user_datum {int /*<<< orphan*/  dfltlevel; int /*<<< orphan*/  range; int /*<<< orphan*/  roles; void* bounds; void* value; } ;
struct policydb {scalar_t__ policyvers; } ;
struct hashtab {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;
typedef  char __le32 ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ POLICYDB_VERSION_BOUNDARY ; 
 scalar_t__ POLICYDB_VERSION_MLS ; 
 int ebitmap_read (int /*<<< orphan*/ *,void*) ; 
 int hashtab_insert (struct hashtab*,char*,struct user_datum*) ; 
 char* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct user_datum* kzalloc (int,int /*<<< orphan*/ ) ; 
 void* le32_to_cpu (char) ; 
 int mls_read_level (int /*<<< orphan*/ *,void*) ; 
 int mls_read_range_helper (int /*<<< orphan*/ *,void*) ; 
 int next_entry (char*,void*,int) ; 
 int /*<<< orphan*/  user_destroy (char*,struct user_datum*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int user_read(struct policydb *p, struct hashtab *h, void *fp)
{
	char *key = NULL;
	struct user_datum *usrdatum;
	int rc, to_read = 2;
	__le32 buf[3];
	u32 len;

	usrdatum = kzalloc(sizeof(*usrdatum), GFP_KERNEL);
	if (!usrdatum) {
		rc = -ENOMEM;
		goto out;
	}

	if (p->policyvers >= POLICYDB_VERSION_BOUNDARY)
		to_read = 3;

	rc = next_entry(buf, fp, sizeof(buf[0]) * to_read);
	if (rc < 0)
		goto bad;

	len = le32_to_cpu(buf[0]);
	usrdatum->value = le32_to_cpu(buf[1]);
	if (p->policyvers >= POLICYDB_VERSION_BOUNDARY)
		usrdatum->bounds = le32_to_cpu(buf[2]);

	key = kmalloc(len + 1, GFP_KERNEL);
	if (!key) {
		rc = -ENOMEM;
		goto bad;
	}
	rc = next_entry(key, fp, len);
	if (rc < 0)
		goto bad;
	key[len] = '\0';

	rc = ebitmap_read(&usrdatum->roles, fp);
	if (rc)
		goto bad;

	if (p->policyvers >= POLICYDB_VERSION_MLS) {
		rc = mls_read_range_helper(&usrdatum->range, fp);
		if (rc)
			goto bad;
		rc = mls_read_level(&usrdatum->dfltlevel, fp);
		if (rc)
			goto bad;
	}

	rc = hashtab_insert(h, key, usrdatum);
	if (rc)
		goto bad;
out:
	return rc;
bad:
	user_destroy(key, usrdatum, NULL);
	goto out;
}