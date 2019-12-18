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
struct smb_sb_info {int /*<<< orphan*/  rstate; } ;

/* Variables and functions */
 int /*<<< orphan*/  PARANOIA (char*) ; 
 int /*<<< orphan*/  SMB_RECV_DROP ; 

__attribute__((used)) static void smbiod_handle_request(struct smb_sb_info *server)
{
	PARANOIA("smbiod got a request ... and we don't implement oplocks!\n");
	server->rstate = SMB_RECV_DROP;
}