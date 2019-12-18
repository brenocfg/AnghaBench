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
struct inode_smack {char* smk_inode; int /*<<< orphan*/  smk_lock; scalar_t__ smk_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct inode_smack* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

struct inode_smack *new_inode_smack(char *smack)
{
	struct inode_smack *isp;

	isp = kzalloc(sizeof(struct inode_smack), GFP_KERNEL);
	if (isp == NULL)
		return NULL;

	isp->smk_inode = smack;
	isp->smk_flags = 0;
	mutex_init(&isp->smk_lock);

	return isp;
}