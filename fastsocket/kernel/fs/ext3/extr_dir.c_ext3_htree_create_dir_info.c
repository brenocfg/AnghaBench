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
struct dir_private_info {int /*<<< orphan*/  curr_minor_hash; int /*<<< orphan*/  curr_hash; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct dir_private_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pos2maj_hash (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pos2min_hash (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct dir_private_info *ext3_htree_create_dir_info(loff_t pos)
{
	struct dir_private_info *p;

	p = kzalloc(sizeof(struct dir_private_info), GFP_KERNEL);
	if (!p)
		return NULL;
	p->curr_hash = pos2maj_hash(pos);
	p->curr_minor_hash = pos2min_hash(pos);
	return p;
}