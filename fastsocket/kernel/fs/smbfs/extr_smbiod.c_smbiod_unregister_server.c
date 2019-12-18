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
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  servers_lock ; 
 int /*<<< orphan*/  smbiod_flush (struct smb_sb_info*) ; 
 int /*<<< orphan*/  smbiod_wake_up () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void smbiod_unregister_server(struct smb_sb_info *server)
{
	spin_lock(&servers_lock);
	list_del_init(&server->entry);
	VERBOSE("%p\n", server);
	spin_unlock(&servers_lock);

	smbiod_wake_up();
	smbiod_flush(server);
}