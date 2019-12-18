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
struct stat_session {int /*<<< orphan*/  stat_mutex; int /*<<< orphan*/  file; } ;

/* Variables and functions */
 int /*<<< orphan*/  __reset_stat_session (struct stat_session*) ; 
 int /*<<< orphan*/  debugfs_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct stat_session*) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void destroy_session(struct stat_session *session)
{
	debugfs_remove(session->file);
	__reset_stat_session(session);
	mutex_destroy(&session->stat_mutex);
	kfree(session);
}