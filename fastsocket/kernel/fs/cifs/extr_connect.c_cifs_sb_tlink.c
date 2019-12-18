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
typedef  int /*<<< orphan*/  uid_t ;
struct tcon_link {struct tcon_link* tl_tcon; int /*<<< orphan*/  tl_flags; scalar_t__ tl_time; int /*<<< orphan*/  tl_uid; } ;
struct cifs_sb_info {int mnt_cifs_flags; int /*<<< orphan*/  tlink_tree_lock; int /*<<< orphan*/  tlink_tree; } ;

/* Variables and functions */
 int CIFS_MOUNT_MULTIUSER ; 
 int EACCES ; 
 int ENOMEM ; 
 struct tcon_link* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct tcon_link*) ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  TCON_LINK_IN_TREE ; 
 int /*<<< orphan*/  TCON_LINK_PENDING ; 
 scalar_t__ TLINK_ERROR_EXPIRE ; 
 struct tcon_link* cifs_construct_tcon (struct cifs_sb_info*,int /*<<< orphan*/ ) ; 
 struct tcon_link* cifs_get_tlink (struct tcon_link*) ; 
 int /*<<< orphan*/  cifs_put_tlink (struct tcon_link*) ; 
 struct tcon_link* cifs_sb_master_tlink (struct cifs_sb_info*) ; 
 int /*<<< orphan*/  cifs_sb_tcon_pending_wait ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current_fsuid () ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  kfree (struct tcon_link*) ; 
 struct tcon_link* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ time_before (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  tlink_rb_insert (int /*<<< orphan*/ *,struct tcon_link*) ; 
 struct tcon_link* tlink_rb_search (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int wait_on_bit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_bit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

struct tcon_link *
cifs_sb_tlink(struct cifs_sb_info *cifs_sb)
{
	int ret;
	uid_t fsuid = current_fsuid();
	struct tcon_link *tlink, *newtlink;

	if (!(cifs_sb->mnt_cifs_flags & CIFS_MOUNT_MULTIUSER))
		return cifs_get_tlink(cifs_sb_master_tlink(cifs_sb));

	spin_lock(&cifs_sb->tlink_tree_lock);
	tlink = tlink_rb_search(&cifs_sb->tlink_tree, fsuid);
	if (tlink)
		cifs_get_tlink(tlink);
	spin_unlock(&cifs_sb->tlink_tree_lock);

	if (tlink == NULL) {
		newtlink = kzalloc(sizeof(*tlink), GFP_KERNEL);
		if (newtlink == NULL)
			return ERR_PTR(-ENOMEM);
		newtlink->tl_uid = fsuid;
		newtlink->tl_tcon = ERR_PTR(-EACCES);
		set_bit(TCON_LINK_PENDING, &newtlink->tl_flags);
		set_bit(TCON_LINK_IN_TREE, &newtlink->tl_flags);
		cifs_get_tlink(newtlink);

		spin_lock(&cifs_sb->tlink_tree_lock);
		/* was one inserted after previous search? */
		tlink = tlink_rb_search(&cifs_sb->tlink_tree, fsuid);
		if (tlink) {
			cifs_get_tlink(tlink);
			spin_unlock(&cifs_sb->tlink_tree_lock);
			kfree(newtlink);
			goto wait_for_construction;
		}
		tlink = newtlink;
		tlink_rb_insert(&cifs_sb->tlink_tree, tlink);
		spin_unlock(&cifs_sb->tlink_tree_lock);
	} else {
wait_for_construction:
		ret = wait_on_bit(&tlink->tl_flags, TCON_LINK_PENDING,
				  cifs_sb_tcon_pending_wait,
				  TASK_INTERRUPTIBLE);
		if (ret) {
			cifs_put_tlink(tlink);
			return ERR_PTR(ret);
		}

		/* if it's good, return it */
		if (!IS_ERR(tlink->tl_tcon))
			return tlink;

		/* return error if we tried this already recently */
		if (time_before(jiffies, tlink->tl_time + TLINK_ERROR_EXPIRE)) {
			cifs_put_tlink(tlink);
			return ERR_PTR(-EACCES);
		}

		if (test_and_set_bit(TCON_LINK_PENDING, &tlink->tl_flags))
			goto wait_for_construction;
	}

	tlink->tl_tcon = cifs_construct_tcon(cifs_sb, fsuid);
	clear_bit(TCON_LINK_PENDING, &tlink->tl_flags);
	wake_up_bit(&tlink->tl_flags, TCON_LINK_PENDING);

	if (IS_ERR(tlink->tl_tcon)) {
		cifs_put_tlink(tlink);
		return ERR_PTR(-EACCES);
	}

	return tlink;
}