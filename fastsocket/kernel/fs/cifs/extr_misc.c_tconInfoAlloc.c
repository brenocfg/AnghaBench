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
struct cifs_tcon {int /*<<< orphan*/  stat_lock; int /*<<< orphan*/  tcon_list; int /*<<< orphan*/  openFileList; int /*<<< orphan*/  tc_count; int /*<<< orphan*/  tidStatus; } ;

/* Variables and functions */
 int /*<<< orphan*/  CifsNew ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 struct cifs_tcon* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tconInfoAllocCount ; 

struct cifs_tcon *
tconInfoAlloc(void)
{
	struct cifs_tcon *ret_buf;
	ret_buf = kzalloc(sizeof(struct cifs_tcon), GFP_KERNEL);
	if (ret_buf) {
		atomic_inc(&tconInfoAllocCount);
		ret_buf->tidStatus = CifsNew;
		++ret_buf->tc_count;
		INIT_LIST_HEAD(&ret_buf->openFileList);
		INIT_LIST_HEAD(&ret_buf->tcon_list);
#ifdef CONFIG_CIFS_STATS
		spin_lock_init(&ret_buf->stat_lock);
#endif
	}
	return ret_buf;
}