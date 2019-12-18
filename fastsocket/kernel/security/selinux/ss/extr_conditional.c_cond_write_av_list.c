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
typedef  scalar_t__ u32 ;
struct policydb {int dummy; } ;
struct policy_file {int dummy; } ;
struct cond_av_list {int /*<<< orphan*/  node; struct cond_av_list* next; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int avtab_write_item (struct policydb*,int /*<<< orphan*/ ,struct policy_file*) ; 
 int /*<<< orphan*/  cpu_to_le32 (scalar_t__) ; 
 int put_entry (int /*<<< orphan*/ *,int,int,struct policy_file*) ; 

__attribute__((used)) static int cond_write_av_list(struct policydb *p,
			      struct cond_av_list *list, struct policy_file *fp)
{
	__le32 buf[1];
	struct cond_av_list *cur_list;
	u32 len;
	int rc;

	len = 0;
	for (cur_list = list; cur_list != NULL; cur_list = cur_list->next)
		len++;

	buf[0] = cpu_to_le32(len);
	rc = put_entry(buf, sizeof(u32), 1, fp);
	if (rc)
		return rc;

	if (len == 0)
		return 0;

	for (cur_list = list; cur_list != NULL; cur_list = cur_list->next) {
		rc = avtab_write_item(p, cur_list->node, fp);
		if (rc)
			return rc;
	}

	return 0;
}