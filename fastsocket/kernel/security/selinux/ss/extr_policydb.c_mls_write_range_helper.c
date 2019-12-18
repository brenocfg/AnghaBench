#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct mls_range {TYPE_1__* level; } ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_3__ {size_t sens; int /*<<< orphan*/  cat; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  cpu_to_le32 (size_t) ; 
 int ebitmap_write (int /*<<< orphan*/ *,void*) ; 
 int mls_level_eq (TYPE_1__*,TYPE_1__*) ; 
 int put_entry (int /*<<< orphan*/ *,int,size_t,void*) ; 

__attribute__((used)) static int mls_write_range_helper(struct mls_range *r, void *fp)
{
	__le32 buf[3];
	size_t items;
	int rc, eq;

	eq = mls_level_eq(&r->level[1], &r->level[0]);

	if (eq)
		items = 2;
	else
		items = 3;
	buf[0] = cpu_to_le32(items-1);
	buf[1] = cpu_to_le32(r->level[0].sens);
	if (!eq)
		buf[2] = cpu_to_le32(r->level[1].sens);

	BUG_ON(items > (sizeof(buf)/sizeof(buf[0])));

	rc = put_entry(buf, sizeof(u32), items, fp);
	if (rc)
		return rc;

	rc = ebitmap_write(&r->level[0].cat, fp);
	if (rc)
		return rc;
	if (!eq) {
		rc = ebitmap_write(&r->level[1].cat, fp);
		if (rc)
			return rc;
	}

	return 0;
}