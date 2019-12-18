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
struct qstr {int dummy; } ;
struct inode {int dummy; } ;
struct gfs2_dirent {int /*<<< orphan*/  de_rec_len; } ;
typedef  int (* gfs2_dscan_t ) (struct gfs2_dirent*,struct qstr const*,void*) ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EIO ; 
 struct gfs2_dirent* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFS2_I (struct inode*) ; 
 unsigned int be16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ gfs2_check_dirent (struct gfs2_dirent*,unsigned int,unsigned int,unsigned int,int) ; 
 int /*<<< orphan*/  gfs2_consist_inode (int /*<<< orphan*/ ) ; 
 int gfs2_dirent_offset (void*) ; 

__attribute__((used)) static struct gfs2_dirent *gfs2_dirent_scan(struct inode *inode, void *buf,
					    unsigned int len, gfs2_dscan_t scan,
					    const struct qstr *name,
					    void *opaque)
{
	struct gfs2_dirent *dent, *prev;
	unsigned offset;
	unsigned size;
	int ret = 0;

	ret = gfs2_dirent_offset(buf);
	if (ret < 0)
		goto consist_inode;

	offset = ret;
	prev = NULL;
	dent = buf + offset;
	size = be16_to_cpu(dent->de_rec_len);
	if (gfs2_check_dirent(dent, offset, size, len, 1))
		goto consist_inode;
	do {
		ret = scan(dent, name, opaque);
		if (ret)
			break;
		offset += size;
		if (offset == len)
			break;
		prev = dent;
		dent = buf + offset;
		size = be16_to_cpu(dent->de_rec_len);
		if (gfs2_check_dirent(dent, offset, size, len, 0))
			goto consist_inode;
	} while(1);

	switch(ret) {
	case 0:
		return NULL;
	case 1:
		return dent;
	case 2:
		return prev ? prev : dent;
	default:
		BUG_ON(ret > 0);
		return ERR_PTR(ret);
	}

consist_inode:
	gfs2_consist_inode(GFS2_I(inode));
	return ERR_PTR(-EIO);
}