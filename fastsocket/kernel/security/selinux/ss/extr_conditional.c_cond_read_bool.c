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
struct hashtab {int dummy; } ;
struct cond_bool_datum {void* state; void* value; } ;
typedef  char __le32 ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  bool_isvalid (struct cond_bool_datum*) ; 
 int /*<<< orphan*/  cond_destroy_bool (char*,struct cond_bool_datum*,int /*<<< orphan*/ *) ; 
 int hashtab_insert (struct hashtab*,char*,struct cond_bool_datum*) ; 
 char* kmalloc (size_t,int /*<<< orphan*/ ) ; 
 struct cond_bool_datum* kzalloc (int,int /*<<< orphan*/ ) ; 
 void* le32_to_cpu (char) ; 
 int next_entry (char*,void*,size_t) ; 

int cond_read_bool(struct policydb *p, struct hashtab *h, void *fp)
{
	char *key = NULL;
	struct cond_bool_datum *booldatum;
	__le32 buf[3];
	u32 len;
	int rc;

	booldatum = kzalloc(sizeof(struct cond_bool_datum), GFP_KERNEL);
	if (!booldatum)
		return -ENOMEM;

	rc = next_entry(buf, fp, sizeof buf);
	if (rc)
		goto err;

	booldatum->value = le32_to_cpu(buf[0]);
	booldatum->state = le32_to_cpu(buf[1]);

	rc = -EINVAL;
	if (!bool_isvalid(booldatum))
		goto err;

	len = le32_to_cpu(buf[2]);

	rc = -ENOMEM;
	key = kmalloc(len + 1, GFP_KERNEL);
	if (!key)
		goto err;
	rc = next_entry(key, fp, len);
	if (rc)
		goto err;
	key[len] = '\0';
	rc = hashtab_insert(h, key, booldatum);
	if (rc)
		goto err;

	return 0;
err:
	cond_destroy_bool(key, booldatum, NULL);
	return rc;
}