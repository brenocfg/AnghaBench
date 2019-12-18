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
struct pt_unit {int /*<<< orphan*/  pi; } ;

/* Variables and functions */
 int /*<<< orphan*/  HZ ; 
 int /*<<< orphan*/  pi_disconnect (int /*<<< orphan*/ ) ; 
 scalar_t__ pt_command (struct pt_unit*,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pt_poll_dsc (struct pt_unit*,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  pt_req_sense (struct pt_unit*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pt_media_access_cmd(struct pt_unit *tape, int tmo, char *cmd, char *fun)
{
	if (pt_command(tape, cmd, 0, fun)) {
		pt_req_sense(tape, 0);
		return;
	}
	pi_disconnect(tape->pi);
	pt_poll_dsc(tape, HZ, tmo, fun);
}