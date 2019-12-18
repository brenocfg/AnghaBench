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
struct qstr {char* name; int /*<<< orphan*/  len; int /*<<< orphan*/  hash; } ;
struct gfs2_sbd {int sd_journals; int /*<<< orphan*/  sd_jindex_mutex; int /*<<< orphan*/  sd_jindex_spin; int /*<<< orphan*/  sd_jindex_list; int /*<<< orphan*/  sd_jindex; } ;
struct gfs2_jdesc {int /*<<< orphan*/  jd_list; scalar_t__ jd_jid; int /*<<< orphan*/  jd_inode; int /*<<< orphan*/  jd_work; int /*<<< orphan*/  extent_list; } ;
struct gfs2_inode {int /*<<< orphan*/  i_gl; } ;
struct gfs2_holder {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct gfs2_inode* GFS2_I (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LM_ST_SHARED ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int gfs2_dir_check (int /*<<< orphan*/ ,struct qstr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gfs2_disk_hash (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_glock_dq_uninit (struct gfs2_holder*) ; 
 int gfs2_glock_nq_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gfs2_holder*) ; 
 int /*<<< orphan*/  gfs2_lookupi (int /*<<< orphan*/ ,struct qstr*,int) ; 
 int /*<<< orphan*/  gfs2_recover_ops ; 
 int /*<<< orphan*/  kfree (struct gfs2_jdesc*) ; 
 struct gfs2_jdesc* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  slow_work_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static int gfs2_jindex_hold(struct gfs2_sbd *sdp, struct gfs2_holder *ji_gh)
{
	struct gfs2_inode *dip = GFS2_I(sdp->sd_jindex);
	struct qstr name;
	char buf[20];
	struct gfs2_jdesc *jd;
	int error;

	name.name = buf;

	mutex_lock(&sdp->sd_jindex_mutex);

	for (;;) {
		error = gfs2_glock_nq_init(dip->i_gl, LM_ST_SHARED, 0, ji_gh);
		if (error)
			break;

		name.len = sprintf(buf, "journal%u", sdp->sd_journals);
		name.hash = gfs2_disk_hash(name.name, name.len);

		error = gfs2_dir_check(sdp->sd_jindex, &name, NULL);
		if (error == -ENOENT) {
			error = 0;
			break;
		}

		gfs2_glock_dq_uninit(ji_gh);

		if (error)
			break;

		error = -ENOMEM;
		jd = kzalloc(sizeof(struct gfs2_jdesc), GFP_KERNEL);
		if (!jd)
			break;

		INIT_LIST_HEAD(&jd->extent_list);
		slow_work_init(&jd->jd_work, &gfs2_recover_ops);
		jd->jd_inode = gfs2_lookupi(sdp->sd_jindex, &name, 1);
		if (!jd->jd_inode || IS_ERR(jd->jd_inode)) {
			if (!jd->jd_inode)
				error = -ENOENT;
			else
				error = PTR_ERR(jd->jd_inode);
			kfree(jd);
			break;
		}

		spin_lock(&sdp->sd_jindex_spin);
		jd->jd_jid = sdp->sd_journals++;
		list_add_tail(&jd->jd_list, &sdp->sd_jindex_list);
		spin_unlock(&sdp->sd_jindex_spin);
	}

	mutex_unlock(&sdp->sd_jindex_mutex);

	return error;
}