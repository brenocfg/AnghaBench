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
struct ncp_server {int /*<<< orphan*/ * name_space; } ;
typedef  size_t __u8 ;
typedef  size_t __u32 ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTK (char*,...) ; 
 int /*<<< orphan*/  ncp_add_byte (struct ncp_server*,int) ; 
 int /*<<< orphan*/  ncp_add_dword (struct ncp_server*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ncp_add_pstring (struct ncp_server*,char const*) ; 
 int /*<<< orphan*/  ncp_get_known_namespace (struct ncp_server*,size_t) ; 
 int /*<<< orphan*/  ncp_init_request (struct ncp_server*) ; 
 size_t ncp_reply_byte (struct ncp_server*,int) ; 
 int /*<<< orphan*/  ncp_reply_dword (struct ncp_server*,int) ; 
 int ncp_request (struct ncp_server*,int) ; 
 int /*<<< orphan*/  ncp_unlock_server (struct ncp_server*) ; 

int 
ncp_get_volume_root(struct ncp_server *server, const char *volname,
		    __u32* volume, __le32* dirent, __le32* dosdirent)
{
	int result;
	__u8 volnum;

	DPRINTK("ncp_get_volume_root: looking up vol %s\n", volname);

	ncp_init_request(server);
	ncp_add_byte(server, 22);	/* Subfunction: Generate dir handle */
	ncp_add_byte(server, 0);	/* DOS namespace */
	ncp_add_byte(server, 0);	/* reserved */
	ncp_add_byte(server, 0);	/* reserved */
	ncp_add_byte(server, 0);	/* reserved */

	ncp_add_byte(server, 0);	/* faked volume number */
	ncp_add_dword(server, 0);	/* faked dir_base */
	ncp_add_byte(server, 0xff);	/* Don't have a dir_base */
	ncp_add_byte(server, 1);	/* 1 path component */
	ncp_add_pstring(server, volname);

	if ((result = ncp_request(server, 87)) != 0) {
		ncp_unlock_server(server);
		return result;
	}
	*dirent = *dosdirent = ncp_reply_dword(server, 4);
	volnum = ncp_reply_byte(server, 8);
	ncp_unlock_server(server);
	*volume = volnum;

	server->name_space[volnum] = ncp_get_known_namespace(server, volnum);

	DPRINTK("lookup_vol: namespace[%d] = %d\n",
		volnum, server->name_space[volnum]);

	return 0;
}