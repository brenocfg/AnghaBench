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
struct ncp_server {int* name_space; } ;
struct inode {int dummy; } ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_2__ {size_t volNumber; int /*<<< orphan*/  dirEntNum; } ;

/* Variables and functions */
 int EINVAL ; 
 TYPE_1__* NCP_FINFO (struct inode*) ; 
 int /*<<< orphan*/  ncp_add_byte (struct ncp_server*,int) ; 
 int /*<<< orphan*/  ncp_add_dword (struct ncp_server*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ncp_add_pstring (struct ncp_server*,char*) ; 
 int /*<<< orphan*/  ncp_add_word (struct ncp_server*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ncp_init_request (struct ncp_server*) ; 
 int ncp_request (struct ncp_server*,int) ; 
 int /*<<< orphan*/  ncp_unlock_server (struct ncp_server*) ; 

__attribute__((used)) static int
ncp_RenameNSEntry(struct ncp_server *server,
		  struct inode *old_dir, char *old_name, __le16 old_type,
		  struct inode *new_dir, char *new_name)
{
	int result = -EINVAL;

	if ((old_dir == NULL) || (old_name == NULL) ||
	    (new_dir == NULL) || (new_name == NULL))
		goto out;

	ncp_init_request(server);
	ncp_add_byte(server, 4);	/* subfunction */
	ncp_add_byte(server, server->name_space[NCP_FINFO(old_dir)->volNumber]);
	ncp_add_byte(server, 1);	/* rename flag */
	ncp_add_word(server, old_type);	/* search attributes */

	/* source Handle Path */
	ncp_add_byte(server, NCP_FINFO(old_dir)->volNumber);
	ncp_add_dword(server, NCP_FINFO(old_dir)->dirEntNum);
	ncp_add_byte(server, 1);
	ncp_add_byte(server, 1);	/* 1 source component */

	/* dest Handle Path */
	ncp_add_byte(server, NCP_FINFO(new_dir)->volNumber);
	ncp_add_dword(server, NCP_FINFO(new_dir)->dirEntNum);
	ncp_add_byte(server, 1);
	ncp_add_byte(server, 1);	/* 1 destination component */

	/* source path string */
	ncp_add_pstring(server, old_name);
	/* dest path string */
	ncp_add_pstring(server, new_name);

	result = ncp_request(server, 87);
	ncp_unlock_server(server);
out:
	return result;
}