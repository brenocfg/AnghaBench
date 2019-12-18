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
typedef  int /*<<< orphan*/  u32 ;
struct policy_data {void* fp; } ;
struct level_datum {size_t isalias; int /*<<< orphan*/  level; } ;
typedef  char __le32 ;

/* Variables and functions */
 char cpu_to_le32 (size_t) ; 
 int mls_write_level (int /*<<< orphan*/ ,void*) ; 
 int put_entry (char*,int,size_t,void*) ; 
 size_t strlen (char*) ; 

__attribute__((used)) static int sens_write(void *vkey, void *datum, void *ptr)
{
	char *key = vkey;
	struct level_datum *levdatum = datum;
	struct policy_data *pd = ptr;
	void *fp = pd->fp;
	__le32 buf[2];
	size_t len;
	int rc;

	len = strlen(key);
	buf[0] = cpu_to_le32(len);
	buf[1] = cpu_to_le32(levdatum->isalias);
	rc = put_entry(buf, sizeof(u32), 2, fp);
	if (rc)
		return rc;

	rc = put_entry(key, 1, len, fp);
	if (rc)
		return rc;

	rc = mls_write_level(levdatum->level, fp);
	if (rc)
		return rc;

	return 0;
}