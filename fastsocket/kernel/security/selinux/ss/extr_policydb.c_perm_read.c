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
typedef  size_t u32 ;
struct policydb {int dummy; } ;
struct perm_datum {void* value; } ;
struct hashtab {int dummy; } ;
typedef  char __le32 ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int hashtab_insert (struct hashtab*,char*,struct perm_datum*) ; 
 char* kmalloc (size_t,int /*<<< orphan*/ ) ; 
 struct perm_datum* kzalloc (int,int /*<<< orphan*/ ) ; 
 void* le32_to_cpu (char) ; 
 int next_entry (char*,void*,size_t) ; 
 int /*<<< orphan*/  perm_destroy (char*,struct perm_datum*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int perm_read(struct policydb *p, struct hashtab *h, void *fp)
{
	char *key = NULL;
	struct perm_datum *perdatum;
	int rc;
	__le32 buf[2];
	u32 len;

	perdatum = kzalloc(sizeof(*perdatum), GFP_KERNEL);
	if (!perdatum) {
		rc = -ENOMEM;
		goto out;
	}

	rc = next_entry(buf, fp, sizeof buf);
	if (rc < 0)
		goto bad;

	len = le32_to_cpu(buf[0]);
	perdatum->value = le32_to_cpu(buf[1]);

	key = kmalloc(len + 1, GFP_KERNEL);
	if (!key) {
		rc = -ENOMEM;
		goto bad;
	}
	rc = next_entry(key, fp, len);
	if (rc < 0)
		goto bad;
	key[len] = '\0';

	rc = hashtab_insert(h, key, perdatum);
	if (rc)
		goto bad;
out:
	return rc;
bad:
	perm_destroy(key, perdatum, NULL);
	goto out;
}