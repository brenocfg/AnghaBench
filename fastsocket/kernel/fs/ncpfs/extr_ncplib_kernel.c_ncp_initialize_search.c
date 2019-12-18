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
struct nw_search_sequence {int dummy; } ;
struct ncp_server {int* name_space; } ;
struct inode {int dummy; } ;
typedef  size_t __u8 ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_2__ {size_t volNumber; int /*<<< orphan*/  dirEntNum; } ;

/* Variables and functions */
 TYPE_1__* NCP_FINFO (struct inode*) ; 
 int /*<<< orphan*/  memcpy (struct nw_search_sequence*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ncp_add_byte (struct ncp_server*,int) ; 
 int /*<<< orphan*/  ncp_add_handle_path (struct ncp_server*,size_t,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ncp_init_request (struct ncp_server*) ; 
 int /*<<< orphan*/  ncp_reply_data (struct ncp_server*,int /*<<< orphan*/ ) ; 
 int ncp_request (struct ncp_server*,int) ; 
 int /*<<< orphan*/  ncp_unlock_server (struct ncp_server*) ; 

int
ncp_initialize_search(struct ncp_server *server, struct inode *dir,
			struct nw_search_sequence *target)
{
	__u8  volnum = NCP_FINFO(dir)->volNumber;
	__le32 dirent = NCP_FINFO(dir)->dirEntNum;
	int result;

	ncp_init_request(server);
	ncp_add_byte(server, 2);	/* subfunction */
	ncp_add_byte(server, server->name_space[volnum]);
	ncp_add_byte(server, 0);	/* reserved */
	ncp_add_handle_path(server, volnum, dirent, 1, NULL);

	result = ncp_request(server, 87);
	if (result)
		goto out;
	memcpy(target, ncp_reply_data(server, 0), sizeof(*target));

out:
	ncp_unlock_server(server);
	return result;
}