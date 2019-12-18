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
struct nfs_server {int /*<<< orphan*/  s_dev; int /*<<< orphan*/  backing_dev_info; } ;

/* Variables and functions */
 int bdi_register_dev (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nfs_bdi_register(struct nfs_server *server)
{
	return bdi_register_dev(&server->backing_dev_info, server->s_dev);
}