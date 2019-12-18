#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ncp_server {int* name_space; } ;
struct TYPE_4__ {int /*<<< orphan*/  volNumber; } ;
struct ncp_entry_info {int opened; TYPE_1__ i; int /*<<< orphan*/  file_handle; int /*<<< orphan*/  volume; } ;
struct inode {int dummy; } ;
typedef  size_t __u8 ;
typedef  int __le32 ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_5__ {size_t volNumber; int dirEntNum; } ;

/* Variables and functions */
 int /*<<< orphan*/  ConvertToNWfromDWORD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* NCP_FINFO (struct inode*) ; 
 int RIM_ALL ; 
 int aDIR ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  ncp_add_byte (struct ncp_server*,int) ; 
 int /*<<< orphan*/  ncp_add_dword (struct ncp_server*,int) ; 
 int /*<<< orphan*/  ncp_add_handle_path (struct ncp_server*,size_t,int,int,char*) ; 
 int /*<<< orphan*/  ncp_add_word (struct ncp_server*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ncp_extract_file_info (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  ncp_init_request (struct ncp_server*) ; 
 int /*<<< orphan*/  ncp_obtain_nfs_info (struct ncp_server*,TYPE_1__*) ; 
 int /*<<< orphan*/  ncp_reply_data (struct ncp_server*,int) ; 
 int /*<<< orphan*/  ncp_reply_le16 (struct ncp_server*,int) ; 
 int ncp_request (struct ncp_server*,int) ; 
 int /*<<< orphan*/  ncp_unlock_server (struct ncp_server*) ; 

int ncp_open_create_file_or_subdir(struct ncp_server *server,
				   struct inode *dir, char *name,
				   int open_create_mode,
				   __le32 create_attributes,
				   __le16 desired_acc_rights,
				   struct ncp_entry_info *target)
{
	__le16 search_attribs = cpu_to_le16(0x0006);
	__u8  volnum;
	__le32 dirent;
	int result;

	volnum = NCP_FINFO(dir)->volNumber;
	dirent = NCP_FINFO(dir)->dirEntNum;

	if ((create_attributes & aDIR) != 0) {
		search_attribs |= cpu_to_le16(0x8000);
	}
	ncp_init_request(server);
	ncp_add_byte(server, 1);	/* subfunction */
	ncp_add_byte(server, server->name_space[volnum]);
	ncp_add_byte(server, open_create_mode);
	ncp_add_word(server, search_attribs);
	ncp_add_dword(server, RIM_ALL);
	ncp_add_dword(server, create_attributes);
	/* The desired acc rights seem to be the inherited rights mask
	   for directories */
	ncp_add_word(server, desired_acc_rights);
	ncp_add_handle_path(server, volnum, dirent, 1, name);

	if ((result = ncp_request(server, 87)) != 0)
		goto out;
	if (!(create_attributes & aDIR))
		target->opened = 1;

	/* in target there's a new finfo to fill */
	ncp_extract_file_info(ncp_reply_data(server, 6), &(target->i));
	target->volume = target->i.volNumber;
	ConvertToNWfromDWORD(ncp_reply_le16(server, 0),
			     ncp_reply_le16(server, 2),
			     target->file_handle);
	
	ncp_unlock_server(server);

	(void)ncp_obtain_nfs_info(server, &(target->i));
	return 0;

out:
	ncp_unlock_server(server);
	return result;
}