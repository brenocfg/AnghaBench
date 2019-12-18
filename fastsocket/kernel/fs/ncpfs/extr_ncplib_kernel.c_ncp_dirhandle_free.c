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

/* Variables and functions */
 int /*<<< orphan*/  ncp_add_byte (struct ncp_server*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ncp_init_request_s (struct ncp_server*,int) ; 
 int ncp_request (struct ncp_server*,int) ; 
 int /*<<< orphan*/  ncp_unlock_server (struct ncp_server*) ; 

int ncp_dirhandle_free(struct ncp_server* server, __u8 dirhandle) {
	int result;
	
	ncp_init_request_s(server, 20);
	ncp_add_byte(server, dirhandle);
	result = ncp_request(server, 22);
	ncp_unlock_server(server);
	return result;
}