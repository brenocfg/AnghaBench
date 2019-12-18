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
struct ncp_server {int dummy; } ;
struct inode {int dummy; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int EACCES ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int ncp_RenameNSEntry (struct ncp_server*,struct inode*,char*,int /*<<< orphan*/ ,struct inode*,char*) ; 
 int ncp_del_file_or_subdir (struct ncp_server*,struct inode*,char*) ; 

int ncp_ren_or_mov_file_or_subdir(struct ncp_server *server,
				struct inode *old_dir, char *old_name,
				struct inode *new_dir, char *new_name)
{
        int result;
        __le16 old_type = cpu_to_le16(0x06);

/* If somebody can do it atomic, call me... vandrove@vc.cvut.cz */
	result = ncp_RenameNSEntry(server, old_dir, old_name, old_type,
	                                   new_dir, new_name);
        if (result == 0xFF)	/* File Not Found, try directory */
	{
		old_type = cpu_to_le16(0x16);
		result = ncp_RenameNSEntry(server, old_dir, old_name, old_type,
						   new_dir, new_name);
	}
	if (result != 0x92) return result;	/* All except NO_FILES_RENAMED */
	result = ncp_del_file_or_subdir(server, new_dir, new_name);
	if (result != 0) return -EACCES;
	result = ncp_RenameNSEntry(server, old_dir, old_name, old_type,
					   new_dir, new_name);
	return result;
}