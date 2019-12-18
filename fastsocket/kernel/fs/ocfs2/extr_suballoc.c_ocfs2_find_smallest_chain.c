#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u16 ;
struct ocfs2_chain_list {TYPE_1__* cl_recs; int /*<<< orphan*/  cl_count; } ;
struct TYPE_2__ {int /*<<< orphan*/  c_total; } ;

/* Variables and functions */
 size_t le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u16 ocfs2_find_smallest_chain(struct ocfs2_chain_list *cl)
{
	u16 curr, best;

	best = curr = 0;
	while (curr < le16_to_cpu(cl->cl_count)) {
		if (le32_to_cpu(cl->cl_recs[best].c_total) >
		    le32_to_cpu(cl->cl_recs[curr].c_total))
			best = curr;
		curr++;
	}
	return best;
}