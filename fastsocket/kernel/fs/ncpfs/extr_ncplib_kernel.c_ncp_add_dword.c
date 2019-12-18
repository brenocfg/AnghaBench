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
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  assert_server_locked (struct ncp_server*) ; 
 int /*<<< orphan*/  put_unaligned (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ncp_add_dword(struct ncp_server *server, __le32 x)
{
	assert_server_locked(server);
	put_unaligned(x, (__le32 *) (&(server->packet[server->current_size])));
	server->current_size += 4;
	return;
}