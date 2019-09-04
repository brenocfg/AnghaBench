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
typedef  int /*<<< orphan*/  user_long_t ;
struct ucred {int dummy; } ;
struct fileglob {int /*<<< orphan*/  fg_label; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_CHECK (int /*<<< orphan*/ ,struct ucred*,struct fileglob*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  file_check_fcntl ; 

int
mac_file_check_fcntl(struct ucred *cred, struct fileglob *fg, int cmd,
    user_long_t arg)
{
	int error;

	MAC_CHECK(file_check_fcntl, cred, fg, fg->fg_label, cmd, arg);
	return (error);
}