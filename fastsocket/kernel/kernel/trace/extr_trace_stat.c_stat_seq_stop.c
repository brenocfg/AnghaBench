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
struct stat_session {int /*<<< orphan*/  stat_mutex; } ;
struct seq_file {struct stat_session* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void stat_seq_stop(struct seq_file *s, void *p)
{
	struct stat_session *session = s->private;
	mutex_unlock(&session->stat_mutex);
}