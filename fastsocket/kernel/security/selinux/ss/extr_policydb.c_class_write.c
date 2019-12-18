#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct policydb {int dummy; } ;
struct policy_data {struct policydb* p; void* fp; } ;
struct constraint_node {struct constraint_node* next; } ;
struct TYPE_3__ {size_t nprim; TYPE_2__* table; } ;
struct class_datum {char* comkey; size_t value; struct constraint_node* validatetrans; struct constraint_node* constraints; TYPE_1__ permissions; } ;
typedef  char __le32 ;
struct TYPE_4__ {size_t nel; } ;

/* Variables and functions */
 char cpu_to_le32 (size_t) ; 
 int hashtab_map (TYPE_2__*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  perm_write ; 
 int put_entry (char*,int,int,void*) ; 
 size_t strlen (char*) ; 
 int write_cons_helper (struct policydb*,struct constraint_node*,void*) ; 

__attribute__((used)) static int class_write(void *vkey, void *datum, void *ptr)
{
	char *key = vkey;
	struct class_datum *cladatum = datum;
	struct policy_data *pd = ptr;
	void *fp = pd->fp;
	struct policydb *p = pd->p;
	struct constraint_node *c;
	__le32 buf[6];
	u32 ncons;
	size_t len, len2;
	int rc;

	len = strlen(key);
	if (cladatum->comkey)
		len2 = strlen(cladatum->comkey);
	else
		len2 = 0;

	ncons = 0;
	for (c = cladatum->constraints; c; c = c->next)
		ncons++;

	buf[0] = cpu_to_le32(len);
	buf[1] = cpu_to_le32(len2);
	buf[2] = cpu_to_le32(cladatum->value);
	buf[3] = cpu_to_le32(cladatum->permissions.nprim);
	if (cladatum->permissions.table)
		buf[4] = cpu_to_le32(cladatum->permissions.table->nel);
	else
		buf[4] = 0;
	buf[5] = cpu_to_le32(ncons);
	rc = put_entry(buf, sizeof(u32), 6, fp);
	if (rc)
		return rc;

	rc = put_entry(key, 1, len, fp);
	if (rc)
		return rc;

	if (cladatum->comkey) {
		rc = put_entry(cladatum->comkey, 1, len2, fp);
		if (rc)
			return rc;
	}

	rc = hashtab_map(cladatum->permissions.table, perm_write, fp);
	if (rc)
		return rc;

	rc = write_cons_helper(p, cladatum->constraints, fp);
	if (rc)
		return rc;

	/* write out the validatetrans rule */
	ncons = 0;
	for (c = cladatum->validatetrans; c; c = c->next)
		ncons++;

	buf[0] = cpu_to_le32(ncons);
	rc = put_entry(buf, sizeof(u32), 1, fp);
	if (rc)
		return rc;

	rc = write_cons_helper(p, cladatum->validatetrans, fp);
	if (rc)
		return rc;

	return 0;
}