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
struct nfs_server {int /*<<< orphan*/  nfs_client; } ;

/* Variables and functions */
 int /*<<< orphan*/  do_renew_lease (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void renew_lease(const struct nfs_server *server, unsigned long timestamp)
{
	do_renew_lease(server->nfs_client, timestamp);
}