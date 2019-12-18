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
struct hpfs_dirent {int dummy; } ;
struct dnode {int dummy; } ;

/* Variables and functions */
 struct hpfs_dirent* de_next_de (struct hpfs_dirent*) ; 
 struct hpfs_dirent* dnode_end_de (struct dnode*) ; 
 struct hpfs_dirent* dnode_first_de (struct dnode*) ; 

__attribute__((used)) static struct hpfs_dirent *dnode_last_de(struct dnode *d)
{
	struct hpfs_dirent *de, *de_end, *dee = NULL;
	de_end = dnode_end_de(d);
	for (de = dnode_first_de(d); de < de_end; de = de_next_de(de)) {
		dee = de;
	}	
	return dee;
}