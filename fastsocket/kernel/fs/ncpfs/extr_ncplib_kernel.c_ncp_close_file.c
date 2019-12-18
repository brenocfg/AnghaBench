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

/* Variables and functions */
 int /*<<< orphan*/  ncp_add_byte (struct ncp_server*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ncp_add_mem (struct ncp_server*,char const*,int) ; 
 int /*<<< orphan*/  ncp_init_request (struct ncp_server*) ; 
 int ncp_request (struct ncp_server*,int) ; 
 int /*<<< orphan*/  ncp_unlock_server (struct ncp_server*) ; 

int
ncp_close_file(struct ncp_server *server, const char *file_id)
{
	int result;

	ncp_init_request(server);
	ncp_add_byte(server, 0);
	ncp_add_mem(server, file_id, 6);

	result = ncp_request(server, 66);
	ncp_unlock_server(server);
	return result;
}