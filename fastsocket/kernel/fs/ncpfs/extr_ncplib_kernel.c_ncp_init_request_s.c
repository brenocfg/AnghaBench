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
struct ncp_server {int current_size; int has_subfunction; } ;
struct ncp_request_header {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ncp_add_byte (struct ncp_server*,int) ; 
 int /*<<< orphan*/  ncp_lock_server (struct ncp_server*) ; 

__attribute__((used)) static inline void ncp_init_request_s(struct ncp_server *server, int subfunction)
{
	ncp_lock_server(server);
	
	server->current_size = sizeof(struct ncp_request_header) + 2;
	ncp_add_byte(server, subfunction);

	server->has_subfunction = 1;
}