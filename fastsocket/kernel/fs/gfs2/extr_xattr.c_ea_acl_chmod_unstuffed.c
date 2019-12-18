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
struct gfs2_sbd {unsigned int sd_jbsize; } ;
struct gfs2_meta_header {int dummy; } ;
struct gfs2_inode {int /*<<< orphan*/  i_gl; int /*<<< orphan*/  i_inode; } ;
struct gfs2_ea_header {int dummy; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  __be64 ;

/* Variables and functions */
 unsigned int DIV_ROUND_UP (unsigned int,unsigned int) ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/ * GFS2_EA2DATAPTRS (struct gfs2_ea_header*) ; 
 unsigned int GFS2_EA_DATA_LEN (struct gfs2_ea_header*) ; 
 int /*<<< orphan*/  GFS2_METATYPE_ED ; 
 struct gfs2_sbd* GFS2_SB (int /*<<< orphan*/ *) ; 
 scalar_t__ RES_DINODE ; 
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int gfs2_meta_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct buffer_head**) ; 
 int gfs2_meta_wait (struct gfs2_sbd*,struct buffer_head*) ; 
 scalar_t__ gfs2_metatype_check (struct gfs2_sbd*,struct buffer_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_trans_add_meta (int /*<<< orphan*/ ,struct buffer_head*) ; 
 int gfs2_trans_begin (struct gfs2_sbd*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_trans_end (struct gfs2_sbd*) ; 
 struct buffer_head** kcalloc (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct buffer_head**) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,char*,unsigned int) ; 

__attribute__((used)) static int ea_acl_chmod_unstuffed(struct gfs2_inode *ip,
				  struct gfs2_ea_header *ea, char *data)
{
	struct gfs2_sbd *sdp = GFS2_SB(&ip->i_inode);
	struct buffer_head **bh;
	unsigned int amount = GFS2_EA_DATA_LEN(ea);
	unsigned int nptrs = DIV_ROUND_UP(amount, sdp->sd_jbsize);
	__be64 *dataptrs = GFS2_EA2DATAPTRS(ea);
	unsigned int x;
	int error;

	bh = kcalloc(nptrs, sizeof(struct buffer_head *), GFP_NOFS);
	if (!bh)
		return -ENOMEM;

	error = gfs2_trans_begin(sdp, nptrs + RES_DINODE, 0);
	if (error)
		goto out;

	for (x = 0; x < nptrs; x++) {
		error = gfs2_meta_read(ip->i_gl, be64_to_cpu(*dataptrs), 0,
				       bh + x);
		if (error) {
			while (x--)
				brelse(bh[x]);
			goto fail;
		}
		dataptrs++;
	}

	for (x = 0; x < nptrs; x++) {
		error = gfs2_meta_wait(sdp, bh[x]);
		if (error) {
			for (; x < nptrs; x++)
				brelse(bh[x]);
			goto fail;
		}
		if (gfs2_metatype_check(sdp, bh[x], GFS2_METATYPE_ED)) {
			for (; x < nptrs; x++)
				brelse(bh[x]);
			error = -EIO;
			goto fail;
		}

		gfs2_trans_add_meta(ip->i_gl, bh[x]);

		memcpy(bh[x]->b_data + sizeof(struct gfs2_meta_header), data,
		       (sdp->sd_jbsize > amount) ? amount : sdp->sd_jbsize);

		amount -= sdp->sd_jbsize;
		data += sdp->sd_jbsize;

		brelse(bh[x]);
	}

out:
	kfree(bh);
	return error;

fail:
	gfs2_trans_end(sdp);
	kfree(bh);
	return error;
}