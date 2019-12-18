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
struct policydb {int /*<<< orphan*/  te_cond_avtab; } ;
struct cond_insertf_data {struct cond_av_list* head; int /*<<< orphan*/ * tail; struct cond_av_list* other; struct policydb* p; } ;
struct cond_av_list {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int avtab_read_item (int /*<<< orphan*/ *,void*,struct policydb*,int /*<<< orphan*/ ,struct cond_insertf_data*) ; 
 int /*<<< orphan*/  cond_insertf ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int next_entry (int /*<<< orphan*/ *,void*,int) ; 

__attribute__((used)) static int cond_read_av_list(struct policydb *p, void *fp, struct cond_av_list **ret_list, struct cond_av_list *other)
{
	int i, rc;
	__le32 buf[1];
	u32 len;
	struct cond_insertf_data data;

	*ret_list = NULL;

	len = 0;
	rc = next_entry(buf, fp, sizeof(u32));
	if (rc)
		return rc;

	len = le32_to_cpu(buf[0]);
	if (len == 0)
		return 0;

	data.p = p;
	data.other = other;
	data.head = NULL;
	data.tail = NULL;
	for (i = 0; i < len; i++) {
		rc = avtab_read_item(&p->te_cond_avtab, fp, p, cond_insertf,
				     &data);
		if (rc)
			return rc;
	}

	*ret_list = data.head;
	return 0;
}