#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct ima_iint_cache {int flags; int /*<<< orphan*/  version; int /*<<< orphan*/  digest; } ;
struct file {TYPE_2__* f_dentry; } ;
struct TYPE_4__ {TYPE_1__* d_inode; } ;
struct TYPE_3__ {int /*<<< orphan*/  i_version; } ;

/* Variables and functions */
 int EEXIST ; 
 int /*<<< orphan*/  IMA_DIGEST_SIZE ; 
 int IMA_MEASURED ; 
 int ima_calc_hash (struct file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ima_collect_measurement(struct ima_iint_cache *iint, struct file *file)
{
	int result = -EEXIST;

	if (!(iint->flags & IMA_MEASURED)) {
		u64 i_version = file->f_dentry->d_inode->i_version;

		memset(iint->digest, 0, IMA_DIGEST_SIZE);
		result = ima_calc_hash(file, iint->digest);
		if (!result)
			iint->version = i_version;
	}
	return result;
}