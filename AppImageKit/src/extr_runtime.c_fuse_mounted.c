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
typedef  int /*<<< orphan*/  pthread_t ;

/* Variables and functions */
 int /*<<< orphan*/  fuse_pid ; 
 int /*<<< orphan*/  getpid () ; 
 int /*<<< orphan*/  keepalive_pipe ; 
 int /*<<< orphan*/  pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_pipe_thread ; 

void
fuse_mounted (void)
{
    pthread_t thread;
    fuse_pid = getpid();
    pthread_create(&thread, NULL, write_pipe_thread, keepalive_pipe);
}