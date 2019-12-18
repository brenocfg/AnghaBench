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
struct ncp_volume_info {unsigned long volume_name; } ;
struct ncp_server {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  volNumber; } ;
struct ncp_entry_info {TYPE_2__ i; int /*<<< orphan*/  volume; } ;
struct ncp_cache_control {int dummy; } ;
struct inode {int dummy; } ;
struct TYPE_3__ {struct dentry* dentry; } ;
struct file {scalar_t__ f_pos; TYPE_1__ f_path; } ;
struct dentry {struct inode* d_inode; } ;
typedef  int /*<<< orphan*/  filldir_t ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTK (char*,unsigned long) ; 
 int NCP_NUMBER_OF_VOLUMES ; 
 struct ncp_server* NCP_SERVER (struct inode*) ; 
 int /*<<< orphan*/  ncp_fill_cache (struct file*,void*,int /*<<< orphan*/ ,struct ncp_cache_control*,struct ncp_entry_info*) ; 
 scalar_t__ ncp_get_volume_info_with_number (struct ncp_server*,int,struct ncp_volume_info*) ; 
 scalar_t__ ncp_lookup_volume (struct ncp_server*,unsigned long,TYPE_2__*) ; 
 int /*<<< orphan*/  strlen (unsigned long) ; 

__attribute__((used)) static void
ncp_read_volume_list(struct file *filp, void *dirent, filldir_t filldir,
			struct ncp_cache_control *ctl)
{
	struct dentry *dentry = filp->f_path.dentry;
	struct inode *inode = dentry->d_inode;
	struct ncp_server *server = NCP_SERVER(inode);
	struct ncp_volume_info info;
	struct ncp_entry_info entry;
	int i;

	DPRINTK("ncp_read_volume_list: pos=%ld\n",
			(unsigned long) filp->f_pos);

	for (i = 0; i < NCP_NUMBER_OF_VOLUMES; i++) {

		if (ncp_get_volume_info_with_number(server, i, &info) != 0)
			return;
		if (!strlen(info.volume_name))
			continue;

		DPRINTK("ncp_read_volume_list: found vol: %s\n",
			info.volume_name);

		if (ncp_lookup_volume(server, info.volume_name,
					&entry.i)) {
			DPRINTK("ncpfs: could not lookup vol %s\n",
				info.volume_name);
			continue;
		}
		entry.volume = entry.i.volNumber;
		if (!ncp_fill_cache(filp, dirent, filldir, ctl, &entry))
			return;
	}
}