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
typedef  int /*<<< orphan*/  __u8 ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int NW_NS_DOS ; 
 int /*<<< orphan*/  ncp_add_byte (struct ncp_server*,int) ; 
 int /*<<< orphan*/  ncp_add_handle_path (struct ncp_server*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ncp_add_word (struct ncp_server*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ncp_init_request (struct ncp_server*) ; 
 int /*<<< orphan*/  ncp_reply_byte (struct ncp_server*,int /*<<< orphan*/ ) ; 
 int ncp_request (struct ncp_server*,int) ; 
 int /*<<< orphan*/  ncp_unlock_server (struct ncp_server*) ; 

int ncp_dirhandle_alloc(struct ncp_server* server, __u8 volnum, __le32 dirent,
			__u8* dirhandle) {
	int result;

	ncp_init_request(server);
	ncp_add_byte(server, 12);		/* subfunction */
	ncp_add_byte(server, NW_NS_DOS);
	ncp_add_byte(server, 0);
	ncp_add_word(server, 0);
	ncp_add_handle_path(server, volnum, dirent, 1, NULL);
	if ((result = ncp_request(server, 87)) == 0) {
		*dirhandle = ncp_reply_byte(server, 0);
	}
	ncp_unlock_server(server);
	return result;
}