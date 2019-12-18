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
struct gfs2_sbd {int sd_rgrps; scalar_t__ sd_max_rg_data; int /*<<< orphan*/  sd_rindex_spin; } ;
struct gfs2_rindex {int /*<<< orphan*/  ri_bitbytes; int /*<<< orphan*/  ri_data; int /*<<< orphan*/  ri_data0; int /*<<< orphan*/  ri_length; int /*<<< orphan*/  ri_addr; } ;
struct gfs2_rgrpd {scalar_t__ rd_data; int /*<<< orphan*/  rd_bits; TYPE_1__* rd_gl; int /*<<< orphan*/  rd_flags; void* rd_addr; int /*<<< orphan*/  rd_rsspin; void* rd_bitbytes; void* rd_data0; void* rd_length; struct gfs2_sbd* rd_sbd; } ;
struct gfs2_inode {int /*<<< orphan*/  i_inode; } ;
struct file_ra_state {int dummy; } ;
typedef  scalar_t__ loff_t ;
struct TYPE_3__ {struct gfs2_rgrpd* gl_object; } ;

/* Variables and functions */
 int /*<<< orphan*/  CREATE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  GFS2_RDF_UPTODATE ; 
 struct gfs2_sbd* GFS2_SB (int /*<<< orphan*/ *) ; 
 void* be32_to_cpu (int /*<<< orphan*/ ) ; 
 void* be64_to_cpu (int /*<<< orphan*/ ) ; 
 int compute_bitstructs (struct gfs2_rgrpd*) ; 
 int gfs2_glock_get (struct gfs2_sbd*,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__**) ; 
 int /*<<< orphan*/  gfs2_glock_put (TYPE_1__*) ; 
 int gfs2_internal_read (struct gfs2_inode*,struct file_ra_state*,char*,scalar_t__*,int) ; 
 int /*<<< orphan*/  gfs2_rgrp_glops ; 
 int /*<<< orphan*/  gfs2_rgrpd_cachep ; 
 scalar_t__ i_size_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct gfs2_rgrpd*) ; 
 struct gfs2_rgrpd* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rgd_insert (struct gfs2_rgrpd*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int read_rindex_entry(struct gfs2_inode *ip,
			     struct file_ra_state *ra_state)
{
	struct gfs2_sbd *sdp = GFS2_SB(&ip->i_inode);
	loff_t pos = sdp->sd_rgrps * sizeof(struct gfs2_rindex);
	struct gfs2_rindex buf;
	int error;
	struct gfs2_rgrpd *rgd;

	if (pos >= i_size_read(&ip->i_inode))
		return 1;

	error = gfs2_internal_read(ip, ra_state, (char *)&buf, &pos,
				   sizeof(struct gfs2_rindex));

	if (error != sizeof(struct gfs2_rindex))
		return (error == 0) ? 1 : error;

	rgd = kmem_cache_zalloc(gfs2_rgrpd_cachep, GFP_NOFS);
	error = -ENOMEM;
	if (!rgd)
		return error;

	rgd->rd_sbd = sdp;
	rgd->rd_addr = be64_to_cpu(buf.ri_addr);
	rgd->rd_length = be32_to_cpu(buf.ri_length);
	rgd->rd_data0 = be64_to_cpu(buf.ri_data0);
	rgd->rd_data = be32_to_cpu(buf.ri_data);
	rgd->rd_bitbytes = be32_to_cpu(buf.ri_bitbytes);
	spin_lock_init(&rgd->rd_rsspin);

	error = compute_bitstructs(rgd);
	if (error)
		goto fail;

	error = gfs2_glock_get(sdp, rgd->rd_addr,
			       &gfs2_rgrp_glops, CREATE, &rgd->rd_gl);
	if (error)
		goto fail;

	rgd->rd_gl->gl_object = rgd;
	rgd->rd_flags &= ~GFS2_RDF_UPTODATE;
	if (rgd->rd_data > sdp->sd_max_rg_data)
		sdp->sd_max_rg_data = rgd->rd_data;
	spin_lock(&sdp->sd_rindex_spin);
	error = rgd_insert(rgd);
	spin_unlock(&sdp->sd_rindex_spin);
	if (!error)
		return 0;

	error = 0; /* someone else read in the rgrp; free it and ignore it */
	gfs2_glock_put(rgd->rd_gl);

fail:
	kfree(rgd->rd_bits);
	kmem_cache_free(gfs2_rgrpd_cachep, rgd);
	return error;
}