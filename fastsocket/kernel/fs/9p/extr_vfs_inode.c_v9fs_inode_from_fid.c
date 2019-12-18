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
struct v9fs_session_info {int dummy; } ;
struct super_block {int dummy; } ;
struct p9_wstat {int /*<<< orphan*/  qid; int /*<<< orphan*/  i_ino; int /*<<< orphan*/  mode; } ;
struct p9_fid {int dummy; } ;
struct inode {int /*<<< orphan*/  qid; int /*<<< orphan*/  i_ino; int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 struct p9_wstat* ERR_CAST (struct p9_wstat*) ; 
 struct p9_wstat* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct p9_wstat*) ; 
 int PTR_ERR (struct p9_wstat*) ; 
 int /*<<< orphan*/  kfree (struct p9_wstat*) ; 
 struct p9_wstat* p9_client_stat (struct p9_fid*) ; 
 int p9mode2unixmode (struct v9fs_session_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p9stat_free (struct p9_wstat*) ; 
 int /*<<< orphan*/  v9fs_cache_inode_get_cookie (struct p9_wstat*) ; 
 struct p9_wstat* v9fs_get_inode (struct super_block*,int) ; 
 int /*<<< orphan*/  v9fs_qid2ino (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v9fs_stat2inode (struct p9_wstat*,struct p9_wstat*,struct super_block*) ; 
 int /*<<< orphan*/  v9fs_vcookie_set_qid (struct p9_wstat*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct inode *
v9fs_inode_from_fid(struct v9fs_session_info *v9ses, struct p9_fid *fid,
	struct super_block *sb)
{
	int err, umode;
	struct inode *ret;
	struct p9_wstat *st;

	ret = NULL;
	st = p9_client_stat(fid);
	if (IS_ERR(st))
		return ERR_CAST(st);

	umode = p9mode2unixmode(v9ses, st->mode);
	ret = v9fs_get_inode(sb, umode);
	if (IS_ERR(ret)) {
		err = PTR_ERR(ret);
		goto error;
	}

	v9fs_stat2inode(st, ret, sb);
	ret->i_ino = v9fs_qid2ino(&st->qid);

#ifdef CONFIG_9P_FSCACHE
	v9fs_vcookie_set_qid(ret, &st->qid);
	v9fs_cache_inode_get_cookie(ret);
#endif
	p9stat_free(st);
	kfree(st);

	return ret;

error:
	p9stat_free(st);
	kfree(st);
	return ERR_PTR(err);
}