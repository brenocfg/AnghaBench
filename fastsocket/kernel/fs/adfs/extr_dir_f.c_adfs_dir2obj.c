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
struct object_info {int /*<<< orphan*/  attr; void* size; void* execaddr; void* loadaddr; void* file_id; int /*<<< orphan*/  name; int /*<<< orphan*/  name_len; } ;
struct adfs_direntry {int /*<<< orphan*/  newdiratts; int /*<<< orphan*/  dirlen; int /*<<< orphan*/  direxec; int /*<<< orphan*/  dirload; int /*<<< orphan*/  dirinddiscadd; int /*<<< orphan*/  dirobname; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADFS_F_NAME_LEN ; 
 int /*<<< orphan*/  adfs_readname (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* adfs_readval (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void
adfs_dir2obj(struct object_info *obj, struct adfs_direntry *de)
{
	obj->name_len =	adfs_readname(obj->name, de->dirobname, ADFS_F_NAME_LEN);
	obj->file_id  = adfs_readval(de->dirinddiscadd, 3);
	obj->loadaddr = adfs_readval(de->dirload, 4);
	obj->execaddr = adfs_readval(de->direxec, 4);
	obj->size     = adfs_readval(de->dirlen,  4);
	obj->attr     = de->newdiratts;
}