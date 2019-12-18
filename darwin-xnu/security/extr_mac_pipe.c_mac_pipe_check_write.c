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
struct pipe {int /*<<< orphan*/  pipe_label; } ;
typedef  int /*<<< orphan*/  kauth_cred_t ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_CHECK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pipe*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mac_pipe_enforce ; 
 int /*<<< orphan*/  pipe_check_write ; 

int
mac_pipe_check_write(kauth_cred_t cred, struct pipe *cpipe)
{
	int error;

#if SECURITY_MAC_CHECK_ENFORCE
    /* 21167099 - only check if we allow write */
    if (!mac_pipe_enforce)
        return (0);
#endif

	MAC_CHECK(pipe_check_write, cred, cpipe, cpipe->pipe_label);

	return (error);
}