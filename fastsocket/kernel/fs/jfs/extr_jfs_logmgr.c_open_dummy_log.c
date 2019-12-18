#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_7__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct super_block {int dummy; } ;
struct jfs_log {int dummy; } ;
struct TYPE_9__ {TYPE_1__* log; int /*<<< orphan*/  log_list; } ;
struct TYPE_8__ {int no_integrity; int size; int /*<<< orphan*/  sb_list; scalar_t__ base; int /*<<< orphan*/  syncwait; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 TYPE_7__* JFS_SBI (struct super_block*) ; 
 int /*<<< orphan*/  LOG_LOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  LOG_UNLOCK (TYPE_1__*) ; 
 TYPE_1__* dummy_log ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jfs_log_mutex ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 TYPE_1__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int lmLogInit (TYPE_1__*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int open_dummy_log(struct super_block *sb)
{
	int rc;

	mutex_lock(&jfs_log_mutex);
	if (!dummy_log) {
		dummy_log = kzalloc(sizeof(struct jfs_log), GFP_KERNEL);
		if (!dummy_log) {
			mutex_unlock(&jfs_log_mutex);
			return -ENOMEM;
		}
		INIT_LIST_HEAD(&dummy_log->sb_list);
		init_waitqueue_head(&dummy_log->syncwait);
		dummy_log->no_integrity = 1;
		/* Make up some stuff */
		dummy_log->base = 0;
		dummy_log->size = 1024;
		rc = lmLogInit(dummy_log);
		if (rc) {
			kfree(dummy_log);
			dummy_log = NULL;
			mutex_unlock(&jfs_log_mutex);
			return rc;
		}
	}

	LOG_LOCK(dummy_log);
	list_add(&JFS_SBI(sb)->log_list, &dummy_log->sb_list);
	JFS_SBI(sb)->log = dummy_log;
	LOG_UNLOCK(dummy_log);
	mutex_unlock(&jfs_log_mutex);

	return 0;
}