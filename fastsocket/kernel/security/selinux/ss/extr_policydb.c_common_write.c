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
typedef  int /*<<< orphan*/  u32 ;
struct policy_data {void* fp; } ;
struct TYPE_3__ {size_t nprim; TYPE_2__* table; } ;
struct common_datum {size_t value; TYPE_1__ permissions; } ;
typedef  char __le32 ;
struct TYPE_4__ {size_t nel; } ;

/* Variables and functions */
 char cpu_to_le32 (size_t) ; 
 int hashtab_map (TYPE_2__*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  perm_write ; 
 int put_entry (char*,int,size_t,void*) ; 
 size_t strlen (char*) ; 

__attribute__((used)) static int common_write(void *vkey, void *datum, void *ptr)
{
	char *key = vkey;
	struct common_datum *comdatum = datum;
	struct policy_data *pd = ptr;
	void *fp = pd->fp;
	__le32 buf[4];
	size_t len;
	int rc;

	len = strlen(key);
	buf[0] = cpu_to_le32(len);
	buf[1] = cpu_to_le32(comdatum->value);
	buf[2] = cpu_to_le32(comdatum->permissions.nprim);
	buf[3] = cpu_to_le32(comdatum->permissions.table->nel);
	rc = put_entry(buf, sizeof(u32), 4, fp);
	if (rc)
		return rc;

	rc = put_entry(key, 1, len, fp);
	if (rc)
		return rc;

	rc = hashtab_map(comdatum->permissions.table, perm_write, fp);
	if (rc)
		return rc;

	return 0;
}