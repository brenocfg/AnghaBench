#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct nw_modify_dos_info {int dummy; } ;
struct ncp_server {int* name_space; } ;
struct inode {int dummy; } ;
typedef  size_t __u8 ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_2__ {size_t volNumber; int /*<<< orphan*/  dirEntNum; } ;

/* Variables and functions */
 TYPE_1__* NCP_FINFO (struct inode*) ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  ncp_add_byte (struct ncp_server*,int) ; 
 int /*<<< orphan*/  ncp_add_dword (struct ncp_server*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ncp_add_handle_path (struct ncp_server*,size_t,int /*<<< orphan*/ ,int,char const*) ; 
 int /*<<< orphan*/  ncp_add_mem (struct ncp_server*,struct nw_modify_dos_info const*,int) ; 
 int /*<<< orphan*/  ncp_add_word (struct ncp_server*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ncp_init_request (struct ncp_server*) ; 
 int ncp_request (struct ncp_server*,int) ; 
 int /*<<< orphan*/  ncp_unlock_server (struct ncp_server*) ; 

int ncp_modify_file_or_subdir_dos_info_path(struct ncp_server *server,
					    struct inode *dir,
					    const char *path,
					    __le32 info_mask,
					    const struct nw_modify_dos_info *info)
{
	__u8  volnum = NCP_FINFO(dir)->volNumber;
	__le32 dirent = NCP_FINFO(dir)->dirEntNum;
	int result;

	ncp_init_request(server);
	ncp_add_byte(server, 7);	/* subfunction */
	ncp_add_byte(server, server->name_space[volnum]);
	ncp_add_byte(server, 0);	/* reserved */
	ncp_add_word(server, cpu_to_le16(0x8006));	/* search attribs: all */

	ncp_add_dword(server, info_mask);
	ncp_add_mem(server, info, sizeof(*info));
	ncp_add_handle_path(server, volnum, dirent, 1, path);

	result = ncp_request(server, 87);
	ncp_unlock_server(server);
	return result;
}