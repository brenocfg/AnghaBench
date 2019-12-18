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

/* Variables and functions */
 scalar_t__ atomic_dec_and_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pipe_users ; 
 int pipe_version ; 
 int /*<<< orphan*/  pipe_version_lock ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void put_pipe_version(void)
{
	if (atomic_dec_and_lock(&pipe_users, &pipe_version_lock)) {
		pipe_version = -1;
		spin_unlock(&pipe_version_lock);
	}
}