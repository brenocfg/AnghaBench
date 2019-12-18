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
struct ncp_server {size_t current_size; int /*<<< orphan*/ * packet; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert_server_locked (struct ncp_server*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void const*,int) ; 

__attribute__((used)) static void ncp_add_mem(struct ncp_server *server, const void *source, int size)
{
	assert_server_locked(server);
	memcpy(&(server->packet[server->current_size]), source, size);
	server->current_size += size;
	return;
}