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
struct smb_sb_info {int /*<<< orphan*/  entry; } ;

/* Variables and functions */
 int /*<<< orphan*/  VERBOSE (char*,struct smb_sb_info*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  servers_lock ; 
 int /*<<< orphan*/  smb_servers ; 
 int smbiod_start () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int smbiod_register_server(struct smb_sb_info *server)
{
	int ret;
	spin_lock(&servers_lock);
	list_add(&server->entry, &smb_servers);
	VERBOSE("%p\n", server);
	ret = smbiod_start();
	spin_unlock(&servers_lock);
	return ret;
}