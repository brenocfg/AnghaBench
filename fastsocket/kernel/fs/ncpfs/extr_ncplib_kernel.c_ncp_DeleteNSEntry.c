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
typedef  int __u8 ;
typedef  int /*<<< orphan*/  __le32 ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  ncp_add_byte (struct ncp_server*,int) ; 
 int /*<<< orphan*/  ncp_add_handle_path (struct ncp_server*,int,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  ncp_add_word (struct ncp_server*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ncp_init_request (struct ncp_server*) ; 
 int ncp_request (struct ncp_server*,int) ; 
 int /*<<< orphan*/  ncp_unlock_server (struct ncp_server*) ; 

__attribute__((used)) static int
ncp_DeleteNSEntry(struct ncp_server *server,
		  __u8 have_dir_base, __u8 volnum, __le32 dirent,
		  char* name, __u8 ns, __le16 attr)
{
	int result;

	ncp_init_request(server);
	ncp_add_byte(server, 8);	/* subfunction */
	ncp_add_byte(server, ns);
	ncp_add_byte(server, 0);	/* reserved */
	ncp_add_word(server, attr);	/* search attribs: all */
	ncp_add_handle_path(server, volnum, dirent, have_dir_base, name);

	result = ncp_request(server, 87);
	ncp_unlock_server(server);
	return result;
}