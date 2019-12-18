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

/* Variables and functions */
 int /*<<< orphan*/  RIM_ALL ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  ncp_add_byte (struct ncp_server*,int) ; 
 int /*<<< orphan*/  ncp_add_dword (struct ncp_server*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ncp_add_handle_path (struct ncp_server*,int,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  ncp_add_word (struct ncp_server*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ncp_init_request (struct ncp_server*) ; 
 int /*<<< orphan*/  ncp_reply_dword (struct ncp_server*,int) ; 
 int ncp_request (struct ncp_server*,int) ; 
 int /*<<< orphan*/  ncp_unlock_server (struct ncp_server*) ; 

__attribute__((used)) static int
ncp_ObtainSpecificDirBase(struct ncp_server *server,
		__u8 nsSrc, __u8 nsDst, __u8 vol_num, __le32 dir_base,
		char *path, /* At most 1 component */
		__le32 *dirEntNum, __le32 *DosDirNum)
{
	int result;

	ncp_init_request(server);
	ncp_add_byte(server, 6); /* subfunction */
	ncp_add_byte(server, nsSrc);
	ncp_add_byte(server, nsDst);
	ncp_add_word(server, cpu_to_le16(0x8006)); /* get all */
	ncp_add_dword(server, RIM_ALL);
	ncp_add_handle_path(server, vol_num, dir_base, 1, path);

	if ((result = ncp_request(server, 87)) != 0)
	{
		ncp_unlock_server(server);
		return result;
	}

	if (dirEntNum)
		*dirEntNum = ncp_reply_dword(server, 0x30);
	if (DosDirNum)
		*DosDirNum = ncp_reply_dword(server, 0x34);
	ncp_unlock_server(server);
	return 0;
}