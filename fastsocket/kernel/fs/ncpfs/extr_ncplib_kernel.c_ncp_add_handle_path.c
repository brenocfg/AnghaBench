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
 int /*<<< orphan*/  ncp_add_byte (struct ncp_server*,int) ; 
 int /*<<< orphan*/  ncp_add_dword (struct ncp_server*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ncp_add_pstring (struct ncp_server*,char const*) ; 

__attribute__((used)) static void ncp_add_handle_path(struct ncp_server *server, __u8 vol_num,
				__le32 dir_base, int have_dir_base, 
				const char *path)
{
	ncp_add_byte(server, vol_num);
	ncp_add_dword(server, dir_base);
	if (have_dir_base != 0) {
		ncp_add_byte(server, 1);	/* dir_base */
	} else {
		ncp_add_byte(server, 0xff);	/* no handle */
	}
	if (path != NULL) {
		ncp_add_byte(server, 1);	/* 1 component */
		ncp_add_pstring(server, path);
	} else {
		ncp_add_byte(server, 0);
	}
}