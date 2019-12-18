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
struct ocfs2_write_ctxt {int w_clen; struct ocfs2_write_cluster_desc* w_desc; } ;
struct ocfs2_write_cluster_desc {int /*<<< orphan*/  c_cpos; int /*<<< orphan*/  c_needs_zero; int /*<<< orphan*/  c_unwritten; int /*<<< orphan*/  c_phys; } ;
struct ocfs2_super {int s_clustersize; } ;
struct ocfs2_alloc_context {int dummy; } ;
struct address_space {TYPE_1__* host; } ;
typedef  int loff_t ;
struct TYPE_2__ {int /*<<< orphan*/  i_sb; } ;

/* Variables and functions */
 struct ocfs2_super* OCFS2_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_write_cluster (struct address_space*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ocfs2_alloc_context*,struct ocfs2_alloc_context*,struct ocfs2_write_ctxt*,int /*<<< orphan*/ ,int,unsigned int) ; 

__attribute__((used)) static int ocfs2_write_cluster_by_desc(struct address_space *mapping,
				       struct ocfs2_alloc_context *data_ac,
				       struct ocfs2_alloc_context *meta_ac,
				       struct ocfs2_write_ctxt *wc,
				       loff_t pos, unsigned len)
{
	int ret, i;
	loff_t cluster_off;
	unsigned int local_len = len;
	struct ocfs2_write_cluster_desc *desc;
	struct ocfs2_super *osb = OCFS2_SB(mapping->host->i_sb);

	for (i = 0; i < wc->w_clen; i++) {
		desc = &wc->w_desc[i];

		/*
		 * We have to make sure that the total write passed in
		 * doesn't extend past a single cluster.
		 */
		local_len = len;
		cluster_off = pos & (osb->s_clustersize - 1);
		if ((cluster_off + local_len) > osb->s_clustersize)
			local_len = osb->s_clustersize - cluster_off;

		ret = ocfs2_write_cluster(mapping, desc->c_phys,
					  desc->c_unwritten,
					  desc->c_needs_zero,
					  data_ac, meta_ac,
					  wc, desc->c_cpos, pos, local_len);
		if (ret) {
			mlog_errno(ret);
			goto out;
		}

		len -= local_len;
		pos += local_len;
	}

	ret = 0;
out:
	return ret;
}